/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ArgsHandler
*/

#include <iostream>
#include <filesystem>

#include "ArgsHandler.hpp"
#include "ExceptionHandling.hpp"

namespace arcade
{
    ArgsHandler::ArgsHandler(int ac, char **av)
    : _argsNb(ac)
    {
        for (int i = 0; av[i] != NULL; i++) {
            std::string to_str(av[i]);
            this->_argsList.push_back(to_str);
        }
        this->_helpList.push_back("-h");
        this->_helpList.push_back("/h");
        this->_helpList.push_back(".h");
        this->_helpList.push_back("--h");
        this->_helpList.push_back("-?");
        this->_helpList.push_back("/?");
        this->_helpList.push_back(".?");
        this->_helpList.push_back("--?");
        this->_helpList.push_back("-help");
        this->_helpList.push_back("/help");
        this->_helpList.push_back(".help");
        this->_helpList.push_back("--help");
    }

    ArgsHandler::~ArgsHandler()
    {
    }

    std::string ArgsHandler::getFileName() const
    {
        return this->_filePath;
    }

    void ArgsHandler::displayHelper() const
    {
        std::cout << "USAGE" << std::endl;
        std::cout << "\t./arcade [dynamic_library_file]\n" << std::endl;
        std::cout << "DESCRIPTION" << std::endl;
        std::cout << "\tdynamic_library_file\tIt must be a '.so' file that represent a dynamic library file" << std::endl;
    }

    void ArgsHandler::checkArguments(int &status)
    {
        int len = 0;

        if (this->_argsNb != 2) {
            std::string msg("Error: The program only handle one argument.\n");
            throw arcade::ArgumentsError(msg);
        }
        for (std::size_t i = 0; i < this->_helpList.size(); i++) {
            if (this->_argsList.at(1) == this->_helpList.at(i)) {
                this->displayHelper();
                status = 1;
                return;
            }
        }
        this->_filePath = this->_argsList.at(1);
        len = this->_filePath.size();
        std::filesystem::path filepath(this->_filePath);
        if (!std::filesystem::exists(filepath)) {
            std::string msg("Error: The given file does not exist.\n");
            throw arcade::ArgumentsError(msg);
        }
        if (this->_filePath.at(len - 1) != 'o' || this->_filePath.at(len - 2) != 's' ||
            this->_filePath.at(len - 3) != '.') {
            std::string msg("Error: The file format must be '.so'.\n");
            throw arcade::ArgumentsError(msg);
        }
    }
}
