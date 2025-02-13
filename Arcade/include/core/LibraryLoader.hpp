/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** LibraryLoader
*/

#pragma once

#include <string>
#include <memory>
#include <dlfcn.h>
#include <iostream>

namespace arcade
{
    class LibraryLoader {
        public:
            LibraryLoader();
            ~LibraryLoader();

            void openLibrary(const std::string &libPath);
            bool isGame() const;
            bool isGraphicLib() const;
            void *getFunction(const std::string &functionName) const;
            void closeLibrary();

        private:

            void *_handle;
    };
}
