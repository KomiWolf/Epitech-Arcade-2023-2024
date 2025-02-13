/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-eric1.xu
** File description:
** Ncurses
*/

#include <memory>

#include "../../include/graphicals/Ncurses.hpp"
#include "../../include/graphicals/NcursesWrapper.hpp"

namespace arcade
{
    Ncurses::Ncurses()
    {
        this->_wrapper = arcade::NcursesWrapper();
    }

    Ncurses::~Ncurses()
    {
    }

    void Ncurses::displayText(const std::string &text, const arcade::Position &pos)
    {
        this->_wrapper.displayText(text, pos);
    }

    void Ncurses::displayBlock(const struct arcade::MapData &mapData)
    {
        this->_wrapper.displayBlock(mapData);
    }

    void Ncurses::clear()
    {
        this->_wrapper.clearWin();
    }

    void Ncurses::refresh()
    {
        this->_wrapper.refreshWin();
    }

    arcade::Event Ncurses::pollEvent()
    {
        return this->_wrapper.pollEvent();
    }
}

extern "C" {
    arcade::IDisplay *createDisplay()
    {
        return std::make_unique<arcade::Ncurses>().release();
    }
}
