/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Nibbler
*/

#pragma once

#include <list>
#include <vector>
#include <string>
#include <thread>

#include "IGame.hpp"

namespace arcade
{
    class Nibbler : public arcade::IGame {
        public:
            Nibbler();
            ~Nibbler();

            void applyCommand(const arcade::KeyBind &bind) override;
            std::vector<arcade::MapData> getMap() override;
            std::size_t getScore() override;
            bool isEnd() override;

        private:
            void _generateFood();
            bool _isCollision();
            void _turnRandomly();
            void _moveNibSnake();
            void _runGame();
            arcade::Position _getNextPose() const;
            std::size_t _getTimer();
            void _decreaseTimer();
            void _startTimerThread();
            void _stopTimerThread();

            const int _width = 23;
            const int _height = 20;
            std::vector<std::string> _map;
            std::list<arcade::Position> _nibSnake;
            arcade::Position _food;
            arcade::Direction _direction;
            bool _gameOver;
            std::size_t _score;
            std::size_t _timer = 990;
            std::thread _timerThread;
            bool _timerRunning = true;
    };
}

extern "C" {
    arcade::IGame *createGame();
}
