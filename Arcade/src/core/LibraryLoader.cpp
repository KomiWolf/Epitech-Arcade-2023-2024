/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** LibraryLoader
*/

#include "ExceptionHandling.hpp"
#include "core/LibraryLoader.hpp"

namespace arcade
{
    LibraryLoader::LibraryLoader()
    {
    }

    LibraryLoader::~LibraryLoader()
    {
    }

    void LibraryLoader::openLibrary(const std::string &libPath)
    {
        this->_handle = dlopen(libPath.c_str(), RTLD_LAZY);
        if (this->_handle == NULL) {
            std::string str(dlerror());
            throw arcade::LibrariesLoaderError(str);
        }
    }

    bool LibraryLoader::isGame() const
    {
        try {
            this->getFunction("createGame");
        } catch (const arcade::LibrariesLoaderError &e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
        return true;
    }

    bool LibraryLoader::isGraphicLib() const
    {
        try {
            this->getFunction("createDisplay");
        } catch (const arcade::LibrariesLoaderError &e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
        return true;
    }

    void *LibraryLoader::getFunction(const std::string &functionName) const
    {
        void *function = NULL;

        function = dlsym(this->_handle, functionName.c_str());
        if (function == NULL) {
            std::string str(dlerror());
            throw arcade::LibrariesLoaderError(str);
        }
        return function;
    }

    void LibraryLoader::closeLibrary()
    {
        dlclose(this->_handle);
    }
}
