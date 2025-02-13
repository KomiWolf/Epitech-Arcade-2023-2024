/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ExceptionHandling
*/

#include <exception>
#include <string>

#pragma once

namespace arcade
{
    class ArgumentsError : public std::exception {
        public:
            ArgumentsError(std::string &msg);
            ~ArgumentsError();

            const char *what() const noexcept override;

        private:
            std::string _errorMsg;
    };

    class LibrariesLoaderError : public std::exception {
        public:
            LibrariesLoaderError(std::string &msg);
            ~LibrariesLoaderError();

            const char *what() const noexcept override;

        private:
            std::string _errorMsg;
    };
}
