/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-eric1.xu
** File description:
** IGame
*/

#pragma once

#include <vector>

#include "LibrariesUtils.hpp"

namespace arcade
{
    class IGame {
        public:
            virtual ~IGame() = default;

            /**
             * @brief This function is here to change the game status depending on
             * the keyboard key pressed provided by the core
             * @param KeyBind The enum class with the key bind pressed
            */
            virtual void applyCommand(const arcade::KeyBind &) = 0;

            /**
             * @brief This function is needed by the core to send map data to
             * the graphical library to display the map
             * @return A vector of the structure "MapData".
            */
            virtual std::vector<arcade::MapData> getMap() = 0;

            /**
             * @brief This function is needed by the core to get the current score of the
             * launched game
             * @return A std::size_t
            */
            virtual std::size_t getScore() = 0;

            /**
             * @brief This function is needed by the core to now when to stop the game
             * in the core
             * @return A bool (true - false)
            */
            virtual bool isEnd() = 0;
    };
}
