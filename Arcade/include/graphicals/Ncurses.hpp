/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurse
*/

#pragma once

#include <memory>

#include "NcursesWrapper.hpp"
#include "../../include/IDisplay.hpp"


namespace arcade
{
    class Ncurses : public arcade::IDisplay {
        public:
            Ncurses();
            ~Ncurses();

            void clear() override;
            void refresh() override;
            arcade::Event pollEvent() override;
            void displayBlock(const struct arcade::MapData &mapData) override;
            void displayText(const std::string &text, const arcade::Position &pos) override;

        private:
            arcade::NcursesWrapper _wrapper;
    };
}

extern "C" {
    arcade::IDisplay *createDisplay();
}
