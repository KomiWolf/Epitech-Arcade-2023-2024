/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/IDisplay.hpp"

namespace arcade
{
    class SDL2 : public arcade::IDisplay {
        public:
            SDL2();
            ~SDL2();

            void clear() override;
            void refresh() override;
            struct arcade::Event pollEvent() override;
            void displayBlock(const struct arcade::MapData &mapData) override;
            void displayText(const std::string &text, const arcade::Position &pos) override;

        private:
            void initSDL2();
            void createWindow();
            void createSprite(const arcade::Position &pos, const std::string &spritePath);

            SDL_Window *_win;
            SDL_Renderer *_renderer;
            TTF_Font *_font;
    };
}

extern "C" {
    arcade::IDisplay *createDisplay();
}
