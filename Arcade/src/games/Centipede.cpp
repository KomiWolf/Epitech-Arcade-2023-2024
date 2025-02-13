/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Centipede
*/

#include <memory>

#include "games/Centipede.hpp"

namespace arcade
{
    GameObject::GameObject(int x, int y, char icon) : x(x), y(y), icon(icon)
    {
    }

    Player::Player(int x, int y) : GameObject(x, y, '^')
    {
    }

    void Player::move(Direction direction) {
        if (direction == Direction::LEFT && x > 0) x--;
        if (direction == Direction::RIGHT && x < WIDTH - 1) x++;
        if (direction == Direction::UP && y > HEIGHT - PLAYER_AREA_HEIGHT) y--;
        if (direction == Direction::DOWN && y < HEIGHT - 1) y++;
    }

    Shot::Shot(int x, int y) : GameObject(x, y, '|')
    {
    }

    bool Shot::move()
    {
        y--;
        return y >= 0;
    }

    CentipedeSegment::CentipedeSegment(int x, int y, bool isHead) : GameObject(x, y, isHead ? 'O' : 'o'), isHead(isHead)
    {
    }

    Obstacle::Obstacle(int x, int y) : GameObject(x, y, 'X'), health(2)
    {
    }

    void Obstacle::hit()
    {
        health--;
    }

    bool Obstacle::isDestroyed()
    {
        return health <= 0;
    }

    Centipede::Centipede() : player(WIDTH / 2, HEIGHT - 1), gameOver(false), score(0), shotCooldown(0), centipedeMoveCooldown(0)
    {
        srand(time(0));
        spawnCentipede();
        generateObstacles();
    }

    Centipede::~Centipede()
    {
    }

    void Centipede::applyCommand(const Event &event)
    {
        char command = event.command;

        if (command == 'k') {
            if (shotCooldown == 0) {
                shots.push_back(Shot(player.x, player.y - 1));
                shotCooldown = 3;
            }
        } else {
            switch (command) {
                case 'q': player.move(Direction::LEFT); break;
                case 'd': player.move(Direction::RIGHT); break;
                case 'z': player.move(Direction::UP); break;
                case 's': player.move(Direction::DOWN); break;
            }
        }
    }

    std::vector<std::string> Centipede::getMap()
    {
        std::vector<std::string> map(HEIGHT, std::string(WIDTH, ' '));

        map[player.y][player.x] = player.icon;

        for (auto& shot : shots) {
            if (shot.y >= 0 && shot.y < HEIGHT) {
                map[shot.y][shot.x] = shot.icon;
            }
        }

        for (auto& centipede : centipedes) {
            for (auto& segment : centipede) {
                map[segment.y][segment.x] = segment.icon;
            }
        }

        for (auto& obstacle : obstacles) {
            if (!obstacle.isDestroyed()) {
                map[obstacle.y][obstacle.x] = obstacle.icon;
            }
        }

        return map;
    }

    std::size_t Centipede::getScore()
    {
        return score;
    }

    bool Centipede::isEnd()
    {
        return gameOver;
    }

    void Centipede::spawnCentipede()
    {
        int numCentipedes = rand() % 4;
        for (int i = 0; i < numCentipedes; ++i) {
            int length = rand() % 8 + 3;
            int startX = rand() % WIDTH;
            std::vector<CentipedeSegment> newCentipede;
            for (int j = 0; j < length; ++j) {
                newCentipede.push_back(CentipedeSegment(startX, j, j == 0));
            }
            centipedes.push_back(newCentipede);
        }
    }

    void Centipede::generateObstacles()
    {
        for (int i = 0; i < 20; ++i) {
            int x = rand() % OBSTACLE_AREA_WIDTH + 1;
            int y = rand() % OBSTACLE_AREA_HEIGHT + 1;
            obstacles.push_back(Obstacle(x, y));
        }
    }

    void Centipede::resetGame()
    {
        centipedes.clear();
        obstacles.clear();
        spawnCentipede();
        generateObstacles();
    }

    void Centipede::update()
    {
        char input = getKeyPress();
        applyCommand(Event(input));

        if (shotCooldown > 0) {
            shotCooldown--;
        }

        for (auto it = shots.begin(); it != shots.end();) {
            if (!it->move()) {
                it = shots.erase(it);
            } else {
                ++it;
            }
        }

        if (centipedeMoveCooldown == 0) {
            moveCentipedes();
            centipedeMoveCooldown = CENTIPEDE_MOVE_COOLDOWN;
        } else {
            centipedeMoveCooldown--;
        }

        for (auto it = shots.begin(); it != shots.end();) {
            bool hit = false;
            for (auto cent_it = centipedes.begin(); cent_it != centipedes.end();) {
                for (size_t j = 0; j < cent_it->size(); ++j) {
                    auto& segment = (*cent_it)[j];
                    if (it->x == segment.x && it->y == segment.y) {
                        obstacles.push_back(Obstacle(segment.x, segment.y));
                        cent_it->erase(cent_it->begin() + j);

                        if (j < cent_it->size() && !cent_it->empty()) {
                            std::vector<CentipedeSegment> newCentipede(cent_it->begin() + j, cent_it->end());
                            cent_it->erase(cent_it->begin() + j, cent_it->end());
                            newCentipede[0].isHead = true;
                            centipedes.push_back(newCentipede);
                        }

                        it = shots.erase(it);
                        score += 10;
                        hit = true;
                        break;
                    }
                }
                if (hit) break;
                if (cent_it->empty()) {
                    cent_it = centipedes.erase(cent_it);
                } else {
                    ++cent_it;
                }
            }
            if (!hit) ++it;
        }

        for (auto it = shots.begin(); it != shots.end();) {
            bool hit = false;
            for (auto& obstacle : obstacles) {
                if (it->x == obstacle.x && it->y == obstacle.y) {
                    obstacle.hit();
                    it = shots.erase(it);
                    hit = true;
                    break;
                }
            }
            if (!hit) ++it;
        }

        for (auto it = obstacles.begin(); it != obstacles.end();) {
            if (it->isDestroyed()) {
                it = obstacles.erase(it);
            } else {
                ++it;
            }
        }

        for (auto& centipede : centipedes) {
            for (auto& segment : centipede) {
                if (player.x == segment.x && player.y == segment.y) {
                    gameOver = true;
                }
            }
        }

        for (auto& centipede : centipedes) {
            for (auto& segment : centipede) {
                if (segment.y >= HEIGHT - PLAYER_AREA_HEIGHT) {
                    gameOver = true;
                }
            }
        }

        if (centipedes.empty()) {
            resetGame();
        }
    }

    void Centipede::moveCentipedes()
    {
        for (auto& centipede : centipedes) {
            if (centipede.empty()) continue;

            std::vector<std::pair<int, int>> previousPositions;
            for (auto& segment : centipede) {
                previousPositions.push_back({segment.x, segment.y});
            }

            CentipedeSegment& head = centipede[0];
            bool hitObstacle = false;
            for (auto& obstacle : obstacles) {
                if (head.x == obstacle.x && head.y + 1 == obstacle.y) {
                    hitObstacle = true;
                    break;
                }
            }
            if (hitObstacle) {
                int direction = rand() % 2 == 0 ? -1 : 1;
                head.x += direction;
                if (head.x < 0) head.x = 0;
                if (head.x >= WIDTH) head.x = WIDTH - 1;
            } else {
                int moveDirection = rand() % 3;
                if (moveDirection == 0 && head.x > 0) {
                    head.x--;
                } else if (moveDirection == 1 && head.x < WIDTH - 1) {
                    head.x++;
                } else {
                    head.y++;
                }
            }

            for (size_t i = 1; i < centipede.size(); ++i) {
                centipede[i].x = previousPositions[i - 1].first;
                centipede[i].y = previousPositions[i - 1].second;
            }
        }
    }

    void Centipede::draw()
    {
        std::vector<std::string> map = getMap();

        for (const std::string& row : map) {
            std::cout << row << std::endl;
        }

        std::cout << "Score: " << score << std::endl;
        std::cout << "Number of centipedes: " << centipedes.size() << std::endl;
        if (gameOver) {
            std::cout << "Game Over!" << std::endl;
        }
    }

    char Centipede::getKeyPress()
    {
        struct termios oldt, newt;
        char ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        return ch;
    }
}

extern "C" {
    arcade::IGame *createGame() {
        return std::make_unique<arcade::Centipede>().release();
    }
}
