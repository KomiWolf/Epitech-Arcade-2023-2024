/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ArgsHandler
*/

#pragma once

#include <string>
#include <vector>

namespace arcade
{
    class ArgsHandler {
        public:
            ArgsHandler(int ac, char **av);
            ~ArgsHandler();

            std::string getFileName() const;
            void displayHelper() const;
            void checkArguments(int &status);

        private:
            int _argsNb;
            std::vector<std::string> _argsList;
            std::vector<std::string> _helpList;
            std::string _filePath;
    };
}
