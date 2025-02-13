/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** main
*/

#include <iostream>

#include "core/Core.hpp"
#include "ExceptionHandling.hpp"
#include "ArgsHandler.hpp"

int main(int ac, char **av)
{
    const int error = 84;
    const int success = 0;
    const int helper = 1;
    int status = 0;
    arcade::ArgsHandler args_handler(ac, av);

    try {
        args_handler.checkArguments(status);
        if (status == helper) {
            status = 0;
            return success;
        }
    } catch (const arcade::ArgumentsError &e) {
        std::cerr << e.what() << std::endl;
        args_handler.displayHelper();
        return error;
    }
    std::string initialDisplayLib(av[1]);

    try {
        arcade::Core core(initialDisplayLib);
        core.runCore();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return error;
    }
    return success;
}
