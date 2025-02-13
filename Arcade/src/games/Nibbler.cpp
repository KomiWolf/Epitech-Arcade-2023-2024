/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Nibbler
*/

#include <chrono>
#include <memory>

#include "games/Nibbler.hpp"

namespace arcade
{
    Nibbler::Nibbler()
    : _direction(arcade::Direction::RIGHT),
    _gameOver(false),
    _score(0),
    _timer(990)
    {
        int nibSnakeStartX = 12;
        int nibSnakeStartY = 18;

        this->_map.push_back("######################");
        this->_map.push_back("#         ##         #");
        this->_map.push_back("# ## #### ## #### ## #");
        this->_map.push_back("#                    #");
        this->_map.push_back("# ## # ######## # ## #");
        this->_map.push_back("#    #    ##    #    #");
        this->_map.push_back("#### #### ## #### ####");
        this->_map.push_back("#    #          #    #");
        this->_map.push_back("# #### ######## #### #");
        this->_map.push_back("#      ########      #");
        this->_map.push_back("#### # ######## # ####");
        this->_map.push_back("#         ##         #");
        this->_map.push_back("# ## #### ## #### ## #");
        this->_map.push_back("#  #              #  #");
        this->_map.push_back("## # # ######## # # ##");
        this->_map.push_back("#    #    ##    #    #");
        this->_map.push_back("# ## #### ## #### ## #");
        this->_map.push_back("# ##    # ## #    ## #");
        this->_map.push_back("#                    #");
        this->_map.push_back("######################");
        this->_nibSnake.push_front({ nibSnakeStartX, nibSnakeStartY });
        this->_nibSnake.push_back({ nibSnakeStartX - 1, nibSnakeStartY });
        this->_nibSnake.push_back({ nibSnakeStartX - 2, nibSnakeStartY });
        this->_nibSnake.push_back({ nibSnakeStartX - 3, nibSnakeStartY });
        for (const auto &pos : this->_nibSnake) {
            this->_map[pos.y][pos.x] = 'B';
        }
        this->_map[nibSnakeStartY][nibSnakeStartX] = 'H';
        this->_generateFood();
    }

    Nibbler::~Nibbler()
    {
        this->_stopTimerThread();
    }

    void Nibbler::applyCommand(const arcade::KeyBind &bind)
    {
        arcade::Position head = this->_nibSnake.front();

        switch (bind) {
            case arcade::KeyBind::UP_KEY:
                if (this->_direction != arcade::Direction::DOWN && this->_map[head.y - 1][head.x] != '#')
                    this->_direction = arcade::Direction::UP;
                break;
            case arcade::KeyBind::DOWN_KEY:
                if (this->_direction != arcade::Direction::UP && this->_map[head.y + 1][head.x] != '#')
                    this->_direction = arcade::Direction::DOWN;
                break;
            case arcade::KeyBind::LEFT_KEY:
                if (this->_direction != arcade::Direction::RIGHT && this->_map[head.y][head.x - 1] != '#')
                    this->_direction = arcade::Direction::LEFT;
                break;
            case arcade::KeyBind::RIGHT_KEY:
                if (this->_direction != arcade::Direction::LEFT && this->_map[head.y][head.x + 1] != '#')
                    this->_direction = arcade::Direction::RIGHT;
                break;
            default:
                break;
        }
    }

    std::vector<arcade::MapData> Nibbler::getMap()
    {
        std::vector<arcade::MapData> map_data_list;
        arcade::MapData map_data;

        this->_runGame();
        for (std::size_t j = 0; j < this->_map.size(); j++) {
            for (std::size_t i = 0; i < this->_map[j].size(); i++) {
                map_data.direction = arcade::Direction::NONE;
                if (this->_map[j][i] == '#') {
                    map_data.type = arcade::BlockType::WALL;
                } else if (this->_map[j][i] == 'O') {
                    map_data.type = arcade::BlockType::APPLE;
                } else if (this->_map[j][i] == 'H') {
                    map_data.direction = this->_direction;
                    map_data.type = arcade::BlockType::SNAKE_HEAD;
                } else if (this->_map[j][i] == 'B') {
                    map_data.type = arcade::BlockType::SNAKE_BODY;
                } else {
                    map_data.type = arcade::BlockType::GROUND;
                }
                map_data.pos.x = i;
                map_data.pos.y = j;
                map_data_list.push_back(map_data);
            }
        }
        return map_data_list;
    }

    std::size_t Nibbler::getScore()
    {
        return this->_score;
    }

    std::size_t Nibbler::_getTimer()
    {
        return this->_timer;
    }

    bool Nibbler::isEnd()
    {
        return this->_gameOver;
    }

    void Nibbler::_generateFood()
    {
        srand(time(0));
        do {
            this->_food.x = rand() % (this->_width - 2) + 1;
            this->_food.y = rand() % (this->_height - 2) + 1;
        } while (this->_map[this->_food.y][this->_food.x] != ' ');
        this->_map[this->_food.y][this->_food.x] = 'O';
    }

    bool Nibbler::_isCollision()
    {
        arcade::Position nextHead = this->_getNextPose();

        if (this->_map[nextHead.y][nextHead.x] == '#') {
            this->_turnRandomly();
            return false;
        }
        return this->_map[nextHead.y][nextHead.x] == 'B' || this->_map[nextHead.y][nextHead.x] == '#';
    }

    void Nibbler::_turnRandomly()
    {
        arcade::Position head = this->_nibSnake.front();
        std::size_t count = 0;
        Direction saveDirection = arcade::Direction::NONE;
        int random = 0;

        if (this->_direction == arcade::Direction::UP || this->_direction == arcade::Direction::DOWN) {
            if (this->_map[head.y][head.x - 1] == ' ') {
                count++;
                saveDirection = arcade::Direction::LEFT;
            }
            if (this->_map[head.y][head.x + 1] == ' ') {
                count++;
                saveDirection = arcade::Direction::RIGHT;
            }
            if (count == 1) {
                this->_direction = saveDirection;
                return;
            }
            if (count == 2) {
                for (int i = 0; i < 10; i++) {
                    random = rand() % 2;
                }
                if (random == 0) {
                    this->_direction = arcade::Direction::LEFT;
                } else {
                    this->_direction = arcade::Direction::RIGHT;
                }
            }
            return;
        }
        if (this->_direction == arcade::Direction::LEFT || this->_direction == arcade::Direction::RIGHT) {
            if (this->_map[head.y - 1][head.x] == ' ') {
                count++;
                saveDirection = arcade::Direction::UP;
            }
            if (this->_map[head.y + 1][head.x] == ' ') {
                count++;
                saveDirection = arcade::Direction::DOWN;
            }
            if (count == 1) {
                this->_direction = saveDirection;
                return;
            }
            if (count == 2) {
                for (int i = 0; i < 10; i++) {
                    random = rand() % 2;
                }
                if (random == 0) {
                    this->_direction = arcade::Direction::UP;
                } else {
                    this->_direction = arcade::Direction::DOWN;
                }
            }
        }
    }

    void Nibbler::_moveNibSnake()
    {
        arcade::Position newHead;

        this->_gameOver = this->_isCollision();
        if (this->_gameOver == true) {
            return;
        }
        newHead = this->_getNextPose();
        this->_map[newHead.y][newHead.x] = 'H';
        for (auto &pos : this->_nibSnake) {
            this->_map[pos.y][pos.x] = 'B';
        }
        this->_nibSnake.push_front(newHead);

        if (newHead.x == this->_food.x && newHead.y == this->_food.y) {
            this->_score += 100;
            this->_generateFood();
        } else {
            this->_map[this->_nibSnake.back().y][this->_nibSnake.back().x] = ' ';
            this->_nibSnake.pop_back();
        }
    }

    Position Nibbler::_getNextPose() const
    {
        arcade::Position nextHead = this->_nibSnake.front();
        switch (this->_direction) {
            case arcade::Direction::UP:
                nextHead.y--;
                break;
            case arcade::Direction::DOWN:
                nextHead.y++;
                break;
            case arcade::Direction::LEFT:
                nextHead.x--;
                break;
            case arcade::Direction::RIGHT:
                nextHead.x++;
                break;
            default:
                break;
        }
        return nextHead;
    }

    void Nibbler::_decreaseTimer()
    {
        if (this->_timer > 0) {
            this->_timer -= 10;
        }
    }

    void Nibbler::_startTimerThread()
    {
        this->_timerThread = std::thread([this]() {
            while (this->_timerRunning && this->_timer > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                this->_decreaseTimer();
            }
        });
    }

    void Nibbler::_stopTimerThread()
    {
        this->_timerRunning = false;
        if (this->_timerThread.joinable()) {
            this->_timerThread.join();
        }
    }

    void Nibbler::_runGame()
    {
        this->_moveNibSnake();
    }
}

extern "C" {
    arcade::IGame *createGame() {
        return std::make_unique<arcade::Nibbler>().release();
    }
}
