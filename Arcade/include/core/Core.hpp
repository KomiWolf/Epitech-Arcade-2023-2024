/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core
*/

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "IGame.hpp"
#include "core/LibraryLoader.hpp"
#include "IDisplay.hpp"

namespace arcade
{
    enum Mode {
        Menu,
        Pause,
        Game,
        ExitProgram
    };

    class Core {
        public:
            Core(std::string &initialDisplayLib);
            ~Core();

            void runCore();

        private:
            void getLibs();
            std::unique_ptr<arcade::IGame> getGameLibPtr(std::size_t &index);
            std::unique_ptr<arcade::IDisplay> getDisplayLibPtr(std::size_t &index);
            bool isLibAlreadyStored(const std::string &libPath);
            std::pair<arcade::LibraryLoader, std::string> generatePair(const std::string &libPath);
            void showCommand();
            void handleMenuEvent();
            void displayMenu();
            void handlePauseEvent();
            void displayPause();
            arcade::KeyBind handleGameEvent();
            void displayGame();
            void closeAllLib();

            std::string _playerName;
            std::size_t _actualScore;
            std::unique_ptr<IDisplay> _display;
            std::unique_ptr<IGame> _game;
            std::vector<std::pair<arcade::LibraryLoader, std::string>> _gameLibs;
            std::vector<std::pair<arcade::LibraryLoader, std::string>> _displayLibs;
            std::size_t _actualDisplayLib;
            std::size_t _actualGameLib;
            std::size_t _displayLibsNb;
            std::size_t _gameLibsNb;
            std::size_t _whichBox;
            Mode _mode;
    };
}
