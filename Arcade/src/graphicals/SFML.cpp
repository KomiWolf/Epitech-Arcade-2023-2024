/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-eric1.xu
** File description:
** SFML
*/

#include <memory>
#include <stdexcept>

#include "graphicals/SFML.hpp"

namespace arcade
{
    SFML::SFML()
    {
        bool fontLoaded = this->_font.loadFromFile("./assets/fonts/arcadeFont.ttf");

        if (fontLoaded == false) {
            throw std::runtime_error("Failed to load font.");
        }
        this->_win.create(sf::VideoMode(1920, 1080, 60), "SFML Display");
    }

    SFML::~SFML()
    {
        this->_win.close();
    }

    void SFML::clear()
    {
        this->_win.clear();
    }

    void SFML::refresh()
    {
        this->_win.display();
    }

    void SFML::displayText(const std::string &text, const arcade::Position &pos)
    {
        sf::Text sfmlText(text, this->_font);

        sfmlText.setPosition(pos.x, pos.y);
        sfmlText.setCharacterSize(16);
        this->_win.draw(sfmlText);
    }

    void SFML::createSprite(const arcade::Position &pos, const std::string &spritePath)
    {
        bool loadTexture = _texture.loadFromFile(spritePath);

        if (loadTexture == false) {
            throw std::runtime_error("Failed to load texture: " + spritePath + ".");
        }
        this->_sprite.setTexture(this->_texture);
        this->_sprite.setPosition(pos.x, pos.y);
        this->_win.draw(this->_sprite);
    }

    void SFML::displayBlock(const struct arcade::MapData &mapData)
    {
        std::string spritePath;

        switch (mapData.type) {
            case BlockType::WALL:
                spritePath = "./assets/sprites/wall.jpg";
                break;
            case BlockType::SNAKE_HEAD:
                spritePath = "./assets/sprites/ground.jpg";
                try {
                    createSprite(mapData.pos, spritePath);
                } catch (const std::runtime_error &e) {
                    throw std::runtime_error(e.what());
                }
                if (mapData.direction == arcade::Direction::UP) {
                    spritePath = "./assets/sprites/snake_head_up.png";
                }
                if (mapData.direction == arcade::Direction::DOWN) {
                    spritePath = "./assets/sprites/snake_head_down.png";
                }
                if (mapData.direction == arcade::Direction::LEFT) {
                    spritePath = "./assets/sprites/snake_head_left.png";
                }
                if (mapData.direction == arcade::Direction::RIGHT) {
                    spritePath = "./assets/sprites/snake_head_right.png";
                }
                break;
            case BlockType::SNAKE_BODY:
                spritePath = "./assets/sprites/snake_body.jpg";
                break;
            case BlockType::APPLE:
                spritePath = "./assets/sprites/ground.jpg";
                try {
                    createSprite(mapData.pos, spritePath);
                } catch (const std::runtime_error &e) {
                    throw std::runtime_error(e.what());
                }
                spritePath = "./assets/sprites/apple.png";
                break;
            case BlockType::GROUND:
                spritePath = "./assets/sprites/ground.jpg";
                break;
            default:
                break;
        }
        try {
            createSprite(mapData.pos, spritePath);
        } catch (const std::runtime_error &e) {
            throw std::runtime_error(e.what());
        }
    }

    arcade::Event SFML::pollEvent()
    {
        arcade::Event event;
        sf::Event sfEvent;

        event.pos = { 0, 0 };
        while (this->_win.pollEvent(sfEvent)) {
            switch (sfEvent.type) {
                case sf::Event::Closed:
                    event.bind = arcade::KeyBind::QUIT_EVENT;
                    break;
                case sf::Event::MouseButtonPressed:
                    event.pos.x = sfEvent.mouseButton.x;
                    event.pos.y = sfEvent.mouseButton.y;
                    if (sfEvent.mouseButton.button == sf::Mouse::Left) {
                        event.bind = arcade::KeyBind::LEFT_MOUSE_KEY;
                    }
                    if (sfEvent.mouseButton.button == sf::Mouse::Right) {
                        event.bind = arcade::KeyBind::RIGHT_MOUSE_KEY;
                    }
                    break;
                case sf::Event::KeyPressed:
                    switch (sfEvent.key.code) {
                        case sf::Keyboard::A:
                            event.bind = arcade::KeyBind::A_KEY;
                            break;
                        case sf::Keyboard::B:
                            event.bind = arcade::KeyBind::B_KEY;
                            break;
                        case sf::Keyboard::C:
                            event.bind = arcade::KeyBind::C_KEY;
                            break;
                        case sf::Keyboard::D:
                            event.bind = arcade::KeyBind::D_KEY;
                            break;
                        case sf::Keyboard::E:
                            event.bind = arcade::KeyBind::E_KEY;
                            break;
                        case sf::Keyboard::F:
                            event.bind = arcade::KeyBind::F_KEY;
                            break;
                        case sf::Keyboard::G:
                            event.bind = arcade::KeyBind::G_KEY;
                            break;
                        case sf::Keyboard::H:
                            event.bind = arcade::KeyBind::H_KEY;
                            break;
                        case sf::Keyboard::I:
                            event.bind = arcade::KeyBind::I_KEY;
                            break;
                        case sf::Keyboard::J:
                            event.bind = arcade::KeyBind::J_KEY;
                            break;
                        case sf::Keyboard::K:
                            event.bind = arcade::KeyBind::K_KEY;
                            break;
                        case sf::Keyboard::L:
                            event.bind = arcade::KeyBind::L_KEY;
                            break;
                        case sf::Keyboard::M:
                            event.bind = arcade::KeyBind::M_KEY;
                            break;
                        case sf::Keyboard::N:
                            event.bind = arcade::KeyBind::N_KEY;
                            break;
                        case sf::Keyboard::O:
                            event.bind = arcade::KeyBind::O_KEY;
                            break;
                        case sf::Keyboard::P:
                            event.bind = arcade::KeyBind::P_KEY;
                            break;
                        case sf::Keyboard::Q:
                            event.bind = arcade::KeyBind::Q_KEY;
                            break;
                        case sf::Keyboard::R:
                            event.bind = arcade::KeyBind::R_KEY;
                            break;
                        case sf::Keyboard::S:
                            event.bind = arcade::KeyBind::S_KEY;
                            break;
                        case sf::Keyboard::T:
                            event.bind = arcade::KeyBind::T_KEY;
                            break;
                        case sf::Keyboard::U:
                            event.bind = arcade::KeyBind::U_KEY;
                            break;
                        case sf::Keyboard::V:
                            event.bind = arcade::KeyBind::V_KEY;
                            break;
                        case sf::Keyboard::W:
                            event.bind = arcade::KeyBind::W_KEY;
                            break;
                        case sf::Keyboard::X:
                            event.bind = arcade::KeyBind::X_KEY;
                            break;
                        case sf::Keyboard::Y:
                            event.bind = arcade::KeyBind::Y_KEY;
                            break;
                        case sf::Keyboard::Z:
                            event.bind = arcade::KeyBind::Z_KEY;
                            break;
                        case sf::Keyboard::Num0:
                            event.bind = arcade::KeyBind::NUM0_KEY;
                            break;
                        case sf::Keyboard::Num1:
                            event.bind = arcade::KeyBind::NUM1_KEY;
                            break;
                        case sf::Keyboard::Num2:
                            event.bind = arcade::KeyBind::NUM2_KEY;
                            break;
                        case sf::Keyboard::Num3:
                            event.bind = arcade::KeyBind::NUM3_KEY;
                            break;
                        case sf::Keyboard::Num4:
                            event.bind = arcade::KeyBind::NUM4_KEY;
                            break;
                        case sf::Keyboard::Num5:
                            event.bind = arcade::KeyBind::NUM5_KEY;
                            break;
                        case sf::Keyboard::Num6:
                            event.bind = arcade::KeyBind::NUM6_KEY;
                            break;
                        case sf::Keyboard::Num7:
                            event.bind = arcade::KeyBind::NUM7_KEY;
                            break;
                        case sf::Keyboard::Num8:
                            event.bind = arcade::KeyBind::NUM8_KEY;
                            break;
                        case sf::Keyboard::Num9:
                            event.bind = arcade::KeyBind::NUM9_KEY;
                            break;
                        case sf::Keyboard::Left:
                            event.bind = arcade::KeyBind::LEFT_KEY;
                            break;
                        case sf::Keyboard::Right:
                            event.bind = arcade::KeyBind::RIGHT_KEY;
                            break;
                        case sf::Keyboard::Up:
                            event.bind = arcade::KeyBind::UP_KEY;
                            break;
                        case sf::Keyboard::Down:
                            event.bind = arcade::KeyBind::DOWN_KEY;
                            break;
                        case sf::Keyboard::Return:
                            event.bind = arcade::KeyBind::ENTER_KEY;
                            break;
                        case sf::Keyboard::Space:
                            event.bind = arcade::KeyBind::SPACE_KEY;
                            break;
                        case sf::Keyboard::Escape:
                            event.bind = arcade::KeyBind::ESCAPE_KEY;
                            break;
                        case sf::Keyboard::BackSpace:
                            event.bind = arcade::KeyBind::BACKSPACE_KEY;
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
        return event;
    }
}

extern "C" {
    arcade::IDisplay *createDisplay()
    {
        return std::make_unique<arcade::SFML>().release();
    }
}
