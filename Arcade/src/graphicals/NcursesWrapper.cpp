/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-eric1.xu
** File description:
** NcursesWrapper
*/

#include <cmath>
#include <string>
#include <stdexcept>

#include "../../include/graphicals/NcursesWrapper.hpp"

namespace arcade
{
    NcursesWrapper::NcursesWrapper()
    {
        initNcurses();
    }

    NcursesWrapper::~NcursesWrapper()
    {
        endwin();
    }

    void NcursesWrapper::initNcurses()
    {
        initscr();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        raw();
        cbreak();
        mouseinterval(0);
    }

    Position NcursesWrapper::getRealPosForNcurses(arcade::Position pos, std::size_t mode)
    {
        Position newPos;
        Position winSize = getWindowSize();

        if (mode == 0) {
            newPos.x = (pos.x * winSize.x) / (double)1920;
            newPos.y = (pos.y * winSize.y) / (double)1080;
            return newPos;
        }
        if (mode == 1) {
            static int x = pos.x;
            static int y = pos.y;
            static const int initialX = x;
            static const int initialY = y;
            static int ncursesX = 125;
            static int ncursesY = 15;

            if (x == pos.x) {
                newPos.x = ncursesX;
            } else {
                x = pos.x;
                if (pos.x == initialX) {
                    ncursesX = 125;
                } else {
                    ncursesX += 1;
                }
                newPos.x = ncursesX;
            }
            if (y == pos.y) {
                newPos.y = ncursesY;
            } else {
                y = pos.y;
                if (pos.y == initialY) {
                    ncursesY = 15;
                } else {
                    ncursesY += 1;
                }
                newPos.y = ncursesY;
            }
        }
        return newPos;
    }

    void NcursesWrapper::displayText(const std::string &text, const arcade::Position &pos)
    {
        Position realPos = getRealPosForNcurses(pos, 0);

        mvprintw(realPos.y, realPos.x, "%s", text.c_str());
    }

    void NcursesWrapper::clearWin()
    {
        clear();
    }

    void NcursesWrapper::refreshWin()
    {
        refresh();
    }

    Position NcursesWrapper::getWindowSize()
    {
        Position size;

        getmaxyx(stdscr, size.y, size.x);
        return size;
    }

    void NcursesWrapper::displayBlock(const struct arcade::MapData &mapData)
    {
        arcade::Position realPos = getRealPosForNcurses(mapData.pos, 1);

        switch (mapData.type) {
            case arcade::BlockType::WALL:
                mvaddch(realPos.y, realPos.x, '#');
                break;
            case arcade::BlockType::GROUND:
                mvaddch(realPos.y, realPos.x, ' ');
                break;
            case arcade::BlockType::APPLE:
                mvaddch(realPos.y, realPos.x, '@');
                break;
            case arcade::BlockType::SNAKE_HEAD:
                if (mapData.direction == arcade::Direction::UP) {
                    mvaddch(realPos.y, realPos.x, '^');
                }
                if (mapData.direction == arcade::Direction::LEFT) {
                    mvaddch(realPos.y, realPos.x, '<');
                }
                if (mapData.direction == arcade::Direction::RIGHT) {
                    mvaddch(realPos.y, realPos.x, '>');
                }
                if (mapData.direction == arcade::Direction::DOWN) {
                    mvaddch(realPos.y, realPos.x, 'v');
                }
                break;
            case arcade::BlockType::SNAKE_BODY:
                mvaddch(realPos.y, realPos.x, 'O');
                break;
            default:
                break;
        }
    }

    arcade::Event NcursesWrapper::pollEvent()
    {
        arcade::Event event;
        int ch = getch();
        MEVENT mouseEvent;

        event.pos = { 0, 0 };
        if (ch != ERR) {
            switch (ch) {
                case KEY_MOUSE:
                    if (getmouse(&mouseEvent) == OK) {
                        event.pos.x = mouseEvent.x;
                        event.pos.y = mouseEvent.y;
                        if (mouseEvent.bstate & BUTTON1_PRESSED) {
                            event.bind = arcade::KeyBind::LEFT_MOUSE_KEY;
                        }
                        if (mouseEvent.bstate & BUTTON2_PRESSED) {
                            event.bind = arcade::KeyBind::RIGHT_MOUSE_KEY;
                        }
                    }
                    break;
                case 'a':
                    event.bind = arcade::KeyBind::A_KEY;
                    break;
                case 'b':
                    event.bind = arcade::KeyBind::B_KEY;
                    break;
                case 'c':
                    event.bind = arcade::KeyBind::C_KEY;
                    break;
                case 'd':
                    event.bind = arcade::KeyBind::D_KEY;
                    break;
                case 'e':
                    event.bind = arcade::KeyBind::E_KEY;
                    break;
                case 'f':
                    event.bind = arcade::KeyBind::F_KEY;
                    break;
                case 'g':
                    event.bind = arcade::KeyBind::G_KEY;
                    break;
                case 'h':
                    event.bind = arcade::KeyBind::H_KEY;
                    break;
                case 'i':
                    event.bind = arcade::KeyBind::I_KEY;
                    break;
                case 'j':
                    event.bind = arcade::KeyBind::J_KEY;
                    break;
                case 'k':
                    event.bind = arcade::KeyBind::K_KEY;
                    break;
                case 'l':
                    event.bind = arcade::KeyBind::L_KEY;
                    break;
                case 'm':
                    event.bind = arcade::KeyBind::M_KEY;
                    break;
                case 'n':
                    event.bind = arcade::KeyBind::N_KEY;
                    break;
                case 'o':
                    event.bind = arcade::KeyBind::O_KEY;
                    break;
                case 'p':
                    event.bind = arcade::KeyBind::P_KEY;
                    break;
                case 'q':
                    event.bind = arcade::KeyBind::Q_KEY;
                    break;
                case 'r':
                    event.bind = arcade::KeyBind::R_KEY;
                    break;
                case 's':
                    event.bind = arcade::KeyBind::S_KEY;
                    break;
                case 't':
                    event.bind = arcade::KeyBind::T_KEY;
                    break;
                case 'u':
                    event.bind = arcade::KeyBind::U_KEY;
                    break;
                case 'v':
                    event.bind = arcade::KeyBind::V_KEY;
                    break;
                case 'w':
                    event.bind = arcade::KeyBind::W_KEY;
                    break;
                case 'x':
                    event.bind = arcade::KeyBind::X_KEY;
                    break;
                case 'y':
                    event.bind = arcade::KeyBind::Y_KEY;
                    break;
                case 'z':
                    event.bind = arcade::KeyBind::Z_KEY;
                    break;
                case '0':
                    event.bind = arcade::KeyBind::NUM0_KEY;
                    break;
                case '1':
                    event.bind = arcade::KeyBind::NUM1_KEY;
                    break;
                case '2':
                    event.bind = arcade::KeyBind::NUM2_KEY;
                    break;
                case '3':
                    event.bind = arcade::KeyBind::NUM3_KEY;
                    break;
                case '4':
                    event.bind = arcade::KeyBind::NUM4_KEY;
                    break;
                case '5':
                    event.bind = arcade::KeyBind::NUM5_KEY;
                    break;
                case '6':
                    event.bind = arcade::KeyBind::NUM6_KEY;
                    break;
                case '7':
                    event.bind = arcade::KeyBind::NUM7_KEY;
                    break;
                case '8':
                    event.bind = arcade::KeyBind::NUM8_KEY;
                    break;
                case '9':
                    event.bind = arcade::KeyBind::NUM9_KEY;
                    break;
                case KEY_LEFT:
                    event.bind = arcade::KeyBind::LEFT_KEY;
                    break;
                case KEY_RIGHT:
                    event.bind = arcade::KeyBind::RIGHT_KEY;
                    break;
                case KEY_UP:
                    event.bind = arcade::KeyBind::UP_KEY;
                    break;
                case KEY_DOWN:
                    event.bind = arcade::KeyBind::DOWN_KEY;
                    break;
                case 27:
                    event.bind = arcade::KeyBind::ESCAPE_KEY;
                    break;
                case KEY_BACKSPACE:
                    event.bind = arcade::KeyBind::BACKSPACE_KEY;
                    break;
                case '\n':
                    event.bind = arcade::KeyBind::ENTER_KEY;
                    break;
                case ' ':
                    event.bind = arcade::KeyBind::SPACE_KEY;
                    break;
                default:
                    break;
            }
        }
        return event;
    }
}
