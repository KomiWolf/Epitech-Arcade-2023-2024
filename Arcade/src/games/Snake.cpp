/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake
*/

#include <chrono>
#include <thread>
#include <string>
#include <memory>

#include "games/Snake.hpp"

namespace arcade
{
    Snake::Snake() 
    : _direction(Direction::RIGHT),
    _gameOver(false),
    _score(0)
    {
        int snakeStartX = this->_width / 2;
        int snakeStartY = this->_height / 2;

        this->_map.resize(this->_height, std::string(this->_width, ' '));
        for (int i = 0; i < this->_width; ++i) {
            this->_map[0][i] = '#';
            this->_map[this->_height - 1][i] = '#';
        }
        for (int i = 0; i < this->_height; ++i) {
            this->_map[i][0] = '#';
            this->_map[i][this->_width - 1] = '#';
        }
        this->_snake.push_front({ snakeStartX, snakeStartY });
        this->_snake.push_back({ snakeStartX - 1, snakeStartY });
        this->_snake.push_back({ snakeStartX - 2, snakeStartY });
        this->_snake.push_back({ snakeStartX - 3, snakeStartY });
        for (const auto &pos : this->_snake) {
            this->_map[pos.y][pos.x] = 'B';
        }
        this->_map[snakeStartY][snakeStartX] = 'H';
        this->_generateFood();
    }

    Snake::~Snake()
    {
    }

    void Snake::applyCommand(const arcade::KeyBind &bind)
    {
        switch (bind) {
            case arcade::KeyBind::UP_KEY:
                if (this->_direction != Direction::DOWN)
                    this->_direction = Direction::UP;
                break;
            case arcade::KeyBind::DOWN_KEY:
                if (this->_direction != Direction::UP)
                    this->_direction = Direction::DOWN;
                break;
            case arcade::KeyBind::LEFT_KEY:
                if (this->_direction != Direction::RIGHT)
                    this->_direction = Direction::LEFT;
                break;
            case arcade::KeyBind::RIGHT_KEY:
                if (this->_direction != Direction::LEFT)
                    this->_direction = Direction::RIGHT;
                break;
            default:
                break;
        }
        this->_runGame();
    }

    std::vector<arcade::MapData> Snake::getMap()
    {
        std::vector<arcade::MapData> map_data_list;
        arcade::MapData map_data;

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

    std::size_t Snake::getScore()
    {
        return this->_score;
    }

    bool Snake::isEnd()
    {
        return this->_gameOver;
    }

    void Snake::_generateFood()
    {
        srand(time(0));
        do {
            this->_food.x = rand() % (this->_width - 2) + 1;
            this->_food.y = rand() % (this->_height - 2) + 1;
        } while (this->_map[this->_food.y][this->_food.x] != ' ');
        this->_map[this->_food.y][this->_food.x] = 'O';
    }

    bool Snake::_isCollision()
    {
        Position nextHead = _getNextPose();

        if (nextHead.x <= 0 || nextHead.x >= this->_width - 1 || nextHead.y <= 0 || nextHead.y >= this->_height - 1) {
            return true;
        }
        for (const auto &pos : this->_snake) {
            if (pos.x == nextHead.x && pos.y == nextHead.y) {
                return true;
            }
        }
        return this->_map[nextHead.y][nextHead.x] == '#' || this->_map[nextHead.y][nextHead.x] == 'B';
    }

    void Snake::_moveSnake()
    {
        Position newHead = this->_getNextPose();

        if (this->_isCollision()) {
            this->_gameOver = true;
            return;
        }
        this->_map[newHead.y][newHead.x] = 'H';
        for (auto &pos : this->_snake) {
            this->_map[pos.y][pos.x] = 'B';
        }
        this->_snake.push_front(newHead);

        if (newHead.x == this->_food.x && newHead.y == this->_food.y) {
            this->_score += 100;
            this->_generateFood();
        } else {
            this->_map[this->_snake.back().y][this->_snake.back().x] = ' ';
            this->_snake.pop_back();
        }
    }

    Position Snake::_getNextPose() const
    {
        Position nextHead = this->_snake.front();

        switch (this->_direction) {
            case Direction::UP:
                nextHead.y--;
                break;
            case Direction::DOWN:
                nextHead.y++;
                break;
            case Direction::LEFT:
                nextHead.x--;
                break;
            case Direction::RIGHT:
                nextHead.x++;
                break;
            default:
                break;
        }
        return nextHead;
    }

    void Snake::_runGame()
    {
        this->_moveSnake();
    }
}

extern "C" {
    arcade::IGame *createGame() {
        return std::make_unique<arcade::Snake>().release();
    }
}
