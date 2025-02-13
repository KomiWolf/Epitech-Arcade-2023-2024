/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Centipede
*/

#ifndef CENTIPEDE_HPP
    #define CENTIPEDE_HPP

    #include <vector>
    #include <iostream>
    #include <cstdlib>
    #include <ctime>
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>

    #include "IGame.hpp"

    const int WIDTH = 23;
    const int HEIGHT = 23;
    const int PLAYER_AREA_HEIGHT = 4;
    const int OBSTACLE_AREA_HEIGHT = 12;
    const int OBSTACLE_AREA_WIDTH = 18;
    const int CENTIPEDE_MOVE_COOLDOWN = 5;

namespace arcade
{
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };

    class GameObject
    {
        public:
            int x, y;
            char icon;
            GameObject(int x, int y, char icon);
    };

    class Player : public GameObject
    {
        public:
            Player(int x, int y);
            void move(Direction direction);
    };

    class Shot : public GameObject
    {
        public:
            Shot(int x, int y);
            bool move();
    };

    class CentipedeSegment : public GameObject
    {
        public:
            bool isHead;
            CentipedeSegment(int x, int y, bool isHead);
    };

    class Obstacle : public GameObject
    {
        public:
            int health;
            Obstacle(int x, int y);
            void hit();
            bool isDestroyed();
    };

    class Centipede
    {
        public:
            Centipede();
            ~Centipede();
            void applyCommand(const Event &event) override;
            std::vector<std::string> getMap() override;
            std::size_t getScore() override;
            bool isEnd() override;

        private:
            Player player;
            std::vector<Shot> shots;
            std::vector<std::vector<CentipedeSegment>> centipedes;
            std::vector<Obstacle> obstacles;
            bool gameOver;
            int score;
            int shotCooldown;
            int centipedeMoveCooldown;

            void spawnCentipede();
            void generateObstacles();
            void resetGame();
            void update();
            void moveCentipedes();
            void draw();
            Direction getDirection(char input);
            char getKeyPress();
    };
}

extern "C" {
    arcade::IGame *createGame();
}

#endif // CENTIPEDE_HPP
