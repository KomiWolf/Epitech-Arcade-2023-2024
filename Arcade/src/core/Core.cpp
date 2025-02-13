/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core
*/

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

#include "core/Core.hpp"
#include "ExceptionHandling.hpp"

namespace arcade
{
    Core::Core(std::string &initialDisplayLib)
    : _playerName("player"),
    _actualDisplayLib(0),
    _actualGameLib(0),
    _displayLibsNb(0),
    _gameLibsNb(0),
    _whichBox(0),
    _mode(Menu)
    {
        std::pair<arcade::LibraryLoader, std::string> pair;

        try {
            pair = this->generatePair(initialDisplayLib);
            this->_displayLibs.push_back(pair);
            this->_displayLibsNb++;
            this->getLibs();
        } catch (const std::runtime_error &e) {
            throw std::runtime_error(e.what());
        } catch (const arcade::LibrariesLoaderError &e) {
            throw std::runtime_error(e.what());
        }
    }

    Core::~Core()
    {
    }

    void Core::runCore()
    {
        try {
            this->_display = this->getDisplayLibPtr(this->_actualDisplayLib);
            while (true) {
                this->_display->clear();
                if (this->_mode == Mode::ExitProgram) {
                    break;
                }
                if (this->_mode == Mode::Menu) {
                    this->displayMenu();
                }
                if (this->_mode == Mode::Game) {
                    this->displayGame();
                }
                if (this->_mode == Mode::Pause) {
                    this->displayPause();
                }
                this->_display->refresh();
                if (this->_mode == Mode::Game) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                } else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(20));
                }
            }
            this->_display.reset();
            this->closeAllLib();
        } catch (const std::runtime_error &e) {
            throw std::runtime_error(e.what());
        }
    }

    void Core::getLibs()
    {
        std::filesystem::path folderPath = "./lib/";
        std::pair<LibraryLoader, std::string> loader_pair;
        std::string str;

        if (!std::filesystem::exists(folderPath) || !std::filesystem::is_directory(folderPath)) {
            str.assign(folderPath);
            str.append(" is not found or is not a folder.");
            throw std::runtime_error(str);
        }
        for (auto &inside : std::filesystem::directory_iterator(folderPath)) {
            str.assign(folderPath);
            str.append(inside.path().filename());
            if (isLibAlreadyStored(str)) {
                continue;
            }
            try {
                loader_pair = this->generatePair(str);
            } catch (const std::runtime_error &e) {
                continue;
            }
            if (loader_pair.first.isGame()) {
                this->_gameLibs.push_back(loader_pair);
                this->_gameLibsNb++;
                continue;
            }
            if (loader_pair.first.isGraphicLib()) {
                this->_displayLibs.push_back(loader_pair);
                this->_displayLibsNb++;
                continue;
            }
            loader_pair.first.closeLibrary();
        }
        if (this->_gameLibsNb == 0) {
            throw std::runtime_error("No game found in the './lib/' folder.");
        }
    }

    std::unique_ptr<IGame> Core::getGameLibPtr(std::size_t &index)
    {
        std::string str("createGame");

        try {
            auto newGame = this->_gameLibs[index].first.getFunction(str);
            auto rawGamePointer = ((arcade::IGame *(*)()) newGame)();

            return std::unique_ptr<IGame>(rawGamePointer);
        } catch (const std::runtime_error &e) {
            throw std::runtime_error(e.what());
        }
        return nullptr;
    }

    std::unique_ptr<IDisplay> Core::getDisplayLibPtr(std::size_t &index)
    {
        std::string str("createDisplay");

        try {
            auto newDisplay = this->_displayLibs[index].first.getFunction(str);
            auto rawDisplayPointer = ((arcade::IDisplay *(*)()) newDisplay)();

            return std::unique_ptr<IDisplay>(rawDisplayPointer);
        } catch (const arcade::LibrariesLoaderError &e) {
            throw std::runtime_error(e.what());
        }
        return nullptr;
    }

    bool Core::isLibAlreadyStored(const std::string &libPath)
    {
        for (std::size_t i = 0; i < this->_displayLibs.size(); i++) {
            if (this->_displayLibs[i].second == libPath) {
                return true;
            }
        }
        for (std::size_t i = 0; i < this->_gameLibs.size(); i++) {
            if (this->_gameLibs[i].second == libPath) {
                return true;
            }
        }
        return false;
    }

    std::pair<arcade::LibraryLoader, std::string> Core::generatePair(const std::string &libPath)
    {
        arcade::LibraryLoader loader;
        std::pair<arcade::LibraryLoader, std::string> pair;

        pair.first = loader;
        pair.second = libPath;
        try {
            pair.first.openLibrary(libPath);
        } catch (const arcade::LibrariesLoaderError &e) {
            throw std::runtime_error(e.what());
        }
        return pair;
    }

    void Core::showCommand()
    {
        arcade::Position pos;
        std::string text;

        try {
            pos.x = 20;
            pos.y = 350;
            text.assign("Command:");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Go up -> Up arrow");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Go down -> Down arrow");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Go left -> Left arrow");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Go right -> Right arrow");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Confirm -> Enter key");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Pause game -> P key");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Quit arcade -> Escape key");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Next game -> 9 key");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Previous game -> 8 key");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Next library -> 2 key");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Previous library -> 1 key");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Return to menu -> Enter key");
            this->_display->displayText(text, pos);
            pos.y += 30;
            text.assign("Restart game -> R key");
            this->_display->displayText(text, pos);
        } catch (std::runtime_error &e) {
            throw std::runtime_error(e.what());
        }
    }

    void Core::handleMenuEvent()
    {
        arcade::Event event = this->_display->pollEvent();

        if (event.bind >= arcade::KeyBind::A_KEY && event.bind <= arcade::KeyBind::Z_KEY) {
            if (event.bind == arcade::KeyBind::A_KEY)
                this->_playerName.push_back('a');
            if (event.bind == arcade::KeyBind::B_KEY)
                this->_playerName.push_back('b');
            if (event.bind == arcade::KeyBind::C_KEY)
                this->_playerName.push_back('c');
            if (event.bind == arcade::KeyBind::D_KEY)
                this->_playerName.push_back('d');
            if (event.bind == arcade::KeyBind::E_KEY)
                this->_playerName.push_back('e');
            if (event.bind == arcade::KeyBind::F_KEY)
                this->_playerName.push_back('f');
            if (event.bind == arcade::KeyBind::G_KEY)
                this->_playerName.push_back('g');
            if (event.bind == arcade::KeyBind::H_KEY)
                this->_playerName.push_back('h');
            if (event.bind == arcade::KeyBind::I_KEY)
                this->_playerName.push_back('i');
            if (event.bind == arcade::KeyBind::J_KEY)
                this->_playerName.push_back('j');
            if (event.bind == arcade::KeyBind::K_KEY)
                this->_playerName.push_back('k');
            if (event.bind == arcade::KeyBind::L_KEY)
                this->_playerName.push_back('l');
            if (event.bind == arcade::KeyBind::M_KEY)
                this->_playerName.push_back('m');
            if (event.bind == arcade::KeyBind::N_KEY)
                this->_playerName.push_back('n');
            if (event.bind == arcade::KeyBind::O_KEY)
                this->_playerName.push_back('o');
            if (event.bind == arcade::KeyBind::P_KEY)
                this->_playerName.push_back('p');
            if (event.bind == arcade::KeyBind::Q_KEY)
                this->_playerName.push_back('q');
            if (event.bind == arcade::KeyBind::R_KEY)
                this->_playerName.push_back('r');
            if (event.bind == arcade::KeyBind::S_KEY)
                this->_playerName.push_back('s');
            if (event.bind == arcade::KeyBind::T_KEY)
                this->_playerName.push_back('t');
            if (event.bind == arcade::KeyBind::U_KEY)
                this->_playerName.push_back('u');
            if (event.bind == arcade::KeyBind::V_KEY)
                this->_playerName.push_back('v');
            if (event.bind == arcade::KeyBind::W_KEY)
                this->_playerName.push_back('w');
            if (event.bind == arcade::KeyBind::X_KEY)
                this->_playerName.push_back('x');
            if (event.bind == arcade::KeyBind::Y_KEY)
                this->_playerName.push_back('y');
            if (event.bind == arcade::KeyBind::Z_KEY)
                this->_playerName.push_back('z');
            return;
        }
        switch (event.bind) {
            case arcade::KeyBind::BACKSPACE_KEY:
                if (!this->_playerName.empty()) {
                    this->_playerName.pop_back();
                }
                break;
            case arcade::KeyBind::LEFT_KEY:
                if (this->_whichBox == 0) {
                    this->_whichBox = 1;
                } else {
                    this->_whichBox--;
                }
                break;
            case arcade::KeyBind::RIGHT_KEY:
                this->_whichBox++;
                if (this->_whichBox > 1) {
                    this->_whichBox = 0;
                }
                break;
            case arcade::KeyBind::UP_KEY:
                if (this->_whichBox == 0) {
                    if (this->_actualGameLib == 0) {
                        this->_actualGameLib = this->_gameLibs.size() - 1;
                    } else {
                        this->_actualGameLib--;
                    }
                } else {
                    if (this->_actualDisplayLib == 0) {
                        this->_actualDisplayLib = this->_displayLibs.size() - 1;
                    } else {
                        this->_actualDisplayLib--;
                    }
                    this->_display.reset();
                    this->_display = this->getDisplayLibPtr(this->_actualDisplayLib);
                }
                break;
            case arcade::KeyBind::DOWN_KEY:
                if (this->_whichBox == 0) {
                        this->_actualGameLib++;
                    if (this->_actualGameLib >= this->_gameLibsNb) {
                        this->_actualGameLib = 0;
                    }
                } else {
                    this->_actualDisplayLib++;
                    if (this->_actualDisplayLib >= this->_displayLibsNb) {
                        this->_actualDisplayLib = 0;
                    }
                    this->_display.reset();
                    this->_display = this->getDisplayLibPtr(this->_actualDisplayLib);
                }
                break;
            case arcade::KeyBind::NUM9_KEY:
                this->_actualDisplayLib++;
                if (this->_actualDisplayLib >= this->_displayLibsNb) {
                    this->_actualDisplayLib = 0;
                }
                this->_display.reset();
                this->_display = this->getDisplayLibPtr(this->_actualDisplayLib);
                break;
            case arcade::KeyBind::NUM8_KEY:
                if (this->_actualDisplayLib == 0) {
                    this->_actualDisplayLib = this->_displayLibs.size() - 1;
                } else {
                    this->_actualDisplayLib--;
                }
                this->_display.reset();
                this->_display = this->getDisplayLibPtr(this->_actualDisplayLib);
                break;
            case arcade::KeyBind::NUM2_KEY:
                this->_actualGameLib++;
                if (this->_actualGameLib >= this->_gameLibsNb) {
                    this->_actualGameLib = 0;
                }
                break;
            case arcade::KeyBind::NUM1_KEY:
                if (this->_actualGameLib == 0) {
                    this->_actualGameLib = this->_gameLibs.size() - 1;
                } else {
                    this->_actualGameLib--;
                }
                break;
            case arcade::KeyBind::ENTER_KEY:
                this->_game = this->getGameLibPtr(this->_actualGameLib);
                this->_mode = Mode::Game;
                break;
            case arcade::KeyBind::ESCAPE_KEY:
                this->_mode = Mode::ExitProgram;
                break;
            case arcade::KeyBind::QUIT_EVENT:
                this->_mode = Mode::ExitProgram;
                break;
            default:
                break;
        }
    }

    void Core::displayMenu()
    {
        Position pos;
        std::string text("Welcome ");
        std::size_t namePos = 0;

        this->handleMenuEvent();
        if (this->_mode != Menu) {
            return;
        }

        try {
            // Display "Welcome Player"
            pos.x = 1000;
            pos.y = 100;
            text.append(this->_playerName);
            this->_display->displayText(text, pos);

            // Display "Choose a game:"
            pos.x = 600;
            pos.y = 300;
            text.assign("Choose a game: ");
            this->_display->displayText(text, pos);
            for (std::size_t i = 0; i < this->_gameLibsNb; i++) {
                pos.y += 50;
                namePos = this->_gameLibs.at(i).second.find_last_of("_");
                std::string gameName = this->_gameLibs.at(i).second.substr(namePos + 1);
                namePos = gameName.find(".");
                gameName = gameName.substr(0, namePos);
                if (i == this->_actualGameLib) {
                    if (this->_whichBox == 0) {
                        text.assign("-> ");
                    } else {
                        text.assign("> ");
                    }
                    text.append(gameName);
                    this->_display->displayText(text, pos);
                    continue;
                }
                text.assign(gameName);
                this->_display->displayText(text, pos);
            }

            // Display "Choose a display library:"
            pos.x = 1400;
            pos.y = 300;
            text.assign("Choose a display library: ");
            this->_display->displayText(text, pos);
            for (std::size_t i = 0; i < this->_displayLibsNb; i++) {
                pos.y += 50;
                namePos = this->_displayLibs.at(i).second.find_last_of("_");
                std::string displayName = this->_displayLibs.at(i).second.substr(namePos + 1);
                namePos = displayName.find(".");
                displayName = displayName.substr(0, namePos);

                if (i == this->_actualDisplayLib) {
                    if (this->_whichBox == 1) {
                        text.assign("-> ");
                    } else {
                        text.assign("> ");
                    }
                    text.append(displayName);
                    this->_display->displayText(text, pos);
                    continue;
                }
                text.assign(displayName);
                this->_display->displayText(text, pos);
            }
            this->showCommand();
        } catch (std::runtime_error &e) {
            throw std::runtime_error(e.what());
        }
    }

    void Core::handlePauseEvent()
    {
        arcade::Event event = this->_display->pollEvent();

        switch (event.bind) {
            case arcade::KeyBind::NUM9_KEY:
                this->_actualDisplayLib++;
                if (this->_actualDisplayLib >= this->_displayLibsNb) {
                    this->_actualDisplayLib = 0;
                }
                this->_display.reset();
                this->_display = this->getDisplayLibPtr(this->_actualDisplayLib);
                break;
            case arcade::KeyBind::NUM8_KEY:
                if (this->_actualDisplayLib == 0) {
                    this->_actualDisplayLib = this->_displayLibs.size() - 1;
                } else {
                    this->_actualDisplayLib--;
                }
                this->_display.reset();
                this->_display = this->getDisplayLibPtr(this->_actualDisplayLib);
                break;
            case arcade::KeyBind::SPACE_KEY:
                this->_mode = Mode::Game;
                break;
            case arcade::KeyBind::ESCAPE_KEY:
                this->_game.reset();
                this->_mode = Mode::ExitProgram;
                break;
            case arcade::KeyBind::QUIT_EVENT:
                this->_game.reset();
                this->_mode = Mode::ExitProgram;
                break;
            case arcade::KeyBind::ENTER_KEY:
                this->_game.reset();
                this->_mode = Mode::Menu;
                break;
            default:
                break;
        }
    }

    void Core::displayPause()
    {
        arcade::Position pos;
        std::string text;

        this->handlePauseEvent();
        if (this->_mode != Mode::Pause) {
            return;
        }
        pos.x = 900;
        pos.y = 530;
        text.assign("Press space to continue the game");
        this->_display->displayText(text, pos);
        this->showCommand();
    }

    arcade::KeyBind Core::handleGameEvent()
    {
        arcade::Event event = this->_display->pollEvent();

        switch (event.bind) {
            case arcade::KeyBind::NUM9_KEY:
                this->_actualDisplayLib++;
                if (this->_actualDisplayLib >= this->_displayLibsNb) {
                    this->_actualDisplayLib = 0;
                }
                this->_display.reset();
                this->_display = this->getDisplayLibPtr(this->_actualDisplayLib);
                break;
            case arcade::KeyBind::NUM8_KEY:
                if (this->_actualDisplayLib == 0) {
                    this->_actualDisplayLib = this->_displayLibs.size() - 1;
                } else {
                    this->_actualDisplayLib--;
                }
                this->_display.reset();
                this->_display = this->getDisplayLibPtr(this->_actualDisplayLib);
                break;
            case arcade::KeyBind::QUIT_EVENT:
                this->_game.reset();
                this->_mode = Mode::ExitProgram;
                break;
            case arcade::KeyBind::ESCAPE_KEY:
                this->_game.reset();
                this->_mode = Mode::ExitProgram;
                break;
            case arcade::KeyBind::ENTER_KEY:
                this->_game.reset();
                this->_mode = Mode::Menu;
                break;
            case arcade::KeyBind::P_KEY:
                this->_mode = Mode::Pause;
                break;
            case arcade::KeyBind::R_KEY:
                this->_game.reset();
                this->_game = this->getGameLibPtr(this->_actualGameLib);
                break;
            default:
                break;
        }
        return event.bind;
    }

    void Core::displayGame()
    {
        arcade::Position pos;
        std::string text;
        arcade::KeyBind bind = this->handleGameEvent();
        std::vector<arcade::MapData> gameMap;

        if (this->_mode != Game) {
            return;
        }
        if (this->_game->isEnd() == true) {
            this->_game.reset();
            this->_mode = Mode::Menu;
            return;
        }
        this->_actualScore = this->_game->getScore();
        pos.x = 1100;
        pos.y = 30;
        text.assign("Score: ");
        text.append(std::to_string(this->_actualScore));
        this->_display->displayText(text, pos);
        pos.x = 700;
        pos.y = 60;
        this->_game->applyCommand(bind);
        gameMap = this->_game->getMap();
        for (std::size_t i = 0; i < gameMap.size(); i++) {
            pos.x = 700;
            pos.y = 100;
            pos.x += 40 * gameMap[i].pos.x;
            pos.y += 40 * gameMap[i].pos.y;
            gameMap[i].pos = pos;
            this->_display->displayBlock(gameMap[i]);
        }
        this->showCommand();
    }

    void Core::closeAllLib()
    {
        for (std::size_t i = 0; i < this->_displayLibs.size(); i++) {
            this->_displayLibs[i].first.closeLibrary();
        }
        for (std::size_t i = 0; i < this->_gameLibs.size(); i++) {
            this->_gameLibs[i].first.closeLibrary();
        }
    }
}
