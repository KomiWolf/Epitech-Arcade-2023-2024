/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** NcursesWrapper
*/

#pragma once

#include <ncurses.h>

#include "../../include/IDisplay.hpp"

namespace arcade
{
    class NcursesWrapper
    {
        public:
            NcursesWrapper();
            ~NcursesWrapper();
            void clearWin();
            void refreshWin();
            arcade::Event pollEvent();
            void displayBlock(const struct arcade::MapData &mapData);
            void displayText(const std::string &text, const Position &pos);

        private:
            void initNcurses();
            Position getWindowSize();
            Position getRealPosForNcurses(arcade::Position pos, std::size_t mode);
    };
}
