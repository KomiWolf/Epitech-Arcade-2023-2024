/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ExceptionHandling
*/

#include "ExceptionHandling.hpp"

namespace arcade
{
    ArgumentsError::ArgumentsError(std::string &msg)
    : _errorMsg(msg)
    {}

    ArgumentsError::~ArgumentsError()
    {}

    const char *ArgumentsError::what() const noexcept
    {
        return this->_errorMsg.c_str();
    }

    LibrariesLoaderError::LibrariesLoaderError(std::string &msg)
    : _errorMsg(msg)
    {}

    LibrariesLoaderError::~LibrariesLoaderError()
    {}

    const char *LibrariesLoaderError::what() const noexcept
    {
        return this->_errorMsg.c_str();
    }
}
