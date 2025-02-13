/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake
*/

#pragma once

#include <list>

#include "IGame.hpp"

namespace arcade
{
    class Snake : public arcade::IGame {
        public:
            Snake();
            ~Snake();

            void applyCommand(const arcade::KeyBind &bind) override;
            std::vector<arcade::MapData> getMap() override;
            std::size_t getScore() override;
            bool isEnd() override;

        private:
            void _generateFood();
            bool _isCollision();
            void _moveSnake();
            void _runGame();
            Position _getNextPose() const;

            const int _width = 23;
            const int _height = 20;
            std::vector<std::string> _map;
            std::list<arcade::Position> _snake;
            arcade::Position _food;
            arcade::Direction _direction;
            bool _gameOver;
            std::size_t _score;
    };
}

extern "C" {
    arcade::IGame *createGame();
}
