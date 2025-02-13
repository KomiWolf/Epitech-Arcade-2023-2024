/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-eric1.xu
** File description:
** SFML
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "../../include/IDisplay.hpp"

namespace arcade
{
    class SFML : public arcade::IDisplay {
        public:
            SFML();
            ~SFML();

            void clear() override;
            void refresh() override;
            arcade::Event pollEvent() override;
            void displayBlock(const struct arcade::MapData &mapData) override;
            void displayText(const std::string &text, const arcade::Position &pos) override;

        private:
            void createSprite(const arcade::Position &pos, const std::string &spritePath);

            sf::RenderWindow _win;
            sf::Font _font;
            sf::Texture _texture;
            sf::Sprite _sprite;
    };
}

extern "C" {
    arcade::IDisplay *createDisplay();
}
