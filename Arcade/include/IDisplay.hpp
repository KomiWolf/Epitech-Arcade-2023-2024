/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-eric1.xu
** File description:
** IDisplay
*/

#pragma once

#include "LibrariesUtils.hpp"

namespace arcade
{
    class IDisplay {
        public:
            virtual ~IDisplay() = default;

            /**
             * @brief Clear the window
            */
            virtual void clear() = 0;

            /**
             * @brief Refresh the window
            */
            virtual void refresh() = 0;

            /**
             * @brief That function is needed by the core to get key pressed/event
             * @return The Event structure
            */
            virtual struct arcade::Event pollEvent() = 0;

            /**
             * @brief That function is needed by the core to display the map on the window
             * @param mapData The MapData structure
            */
            virtual void displayBlock(const struct arcade::MapData &) = 0;

            /**
             * @brief That function is needed by the core to display some text on the window
             * @param text The text to display
             * @param position The position of the text on the window
            */
            virtual void displayText(const std::string &, const Position &) = 0;
    };
}
