/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-eric1.xu
** File description:
** SDL2
*/

#include <memory>
#include <stdexcept>
#include <SDL2/SDL_image.h>

#include "graphicals/SDL2.hpp"

namespace arcade
{
    SDL2::SDL2() : _win(nullptr), _renderer(nullptr)
    {
        try {
            this->initSDL2();
            this->createWindow();
        } catch (const std::runtime_error &e) {
            throw std::runtime_error(e.what());
        }
    }

    SDL2::~SDL2()
    {
        SDL_DestroyRenderer(this->_renderer);
        SDL_DestroyWindow(this->_win);
        TTF_CloseFont(this->_font);
        TTF_Quit();
        SDL_Quit();
    }

    void SDL2::initSDL2()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error("Failed to initialize the SDL2 library" + std::string(SDL_GetError()));
        }
        if (TTF_Init() == -1) {
            throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
        }
        this->_font = TTF_OpenFont("./assets/fonts/arcadeFont.ttf", 16);
    }

    void SDL2::createWindow()
    {
        this->_win = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
        if (this->_win == nullptr) {
            throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
        }
        this->_renderer = SDL_CreateRenderer(this->_win, -1, SDL_RENDERER_ACCELERATED);
        if (this->_renderer == nullptr) {
            throw std::runtime_error("Failed to create renderer SDL: " + std::string(SDL_GetError()));
        }
    }

    void SDL2::clear()
    {
        SDL_RenderClear(this->_renderer);
    }

    void SDL2::refresh()
    {
        SDL_RenderPresent(this->_renderer);
    }

    void SDL2::displayText(const std::string &text, const arcade::Position &pos)
    {
        SDL_Color color;
        SDL_Surface *surface = nullptr;
        SDL_Texture *texture = nullptr;

        if (this->_font == nullptr) {
            throw std::runtime_error("Failed to open font: " + std::string(SDL_GetError()));
        }
        color = {255, 255, 255, 255};
        surface = TTF_RenderText_Solid(this->_font, text.c_str(), color);
        if (surface == nullptr) {
            throw std::runtime_error("Failed to create surface render text:" + std::string(SDL_GetError()));
        }
        texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
        if (texture == nullptr) {
            throw std::runtime_error("Failed to create texture:" + std::string(SDL_GetError()));
        }
        SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
        SDL_Rect txtRect ={(int)pos.x, (int)pos.y, surface->w, surface->h};
        SDL_QueryTexture(texture, nullptr, nullptr, &txtRect.w, &txtRect.h);
        SDL_RenderCopy(this->_renderer, texture, nullptr, &txtRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void SDL2::createSprite(const arcade::Position &pos, const std::string &spritePath)
    {
        SDL_Surface *spriteSurface = IMG_Load(spritePath.c_str());
        SDL_Texture *spriteTexture = nullptr;

        if (spriteSurface == nullptr) {
            throw std::runtime_error("Failed to load sprite: " + std::string(SDL_GetError()));
        }
        spriteTexture = SDL_CreateTextureFromSurface(this->_renderer, spriteSurface);

        if (spriteTexture == nullptr) {
            throw std::runtime_error("Failed to create sprite texture: " + std::string(SDL_GetError()));
        }
        SDL_FreeSurface(spriteSurface);
        SDL_Rect spriteRect = {(int)pos.x, (int)pos.y, 40, 40};
        SDL_RenderCopy(this->_renderer, spriteTexture, nullptr, &spriteRect);
        SDL_DestroyTexture(spriteTexture);
    }

    void SDL2::displayBlock(const struct arcade::MapData &mapData)
    {
        std::string spritePath;

        switch (mapData.type) {
            case arcade::BlockType::WALL:
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
            case arcade::BlockType::APPLE:
                spritePath = "./assets/sprites/ground.jpg";
                try {
                    createSprite(mapData.pos, spritePath);
                } catch (const std::runtime_error &e) {
                    throw std::runtime_error(e.what());
                }
                spritePath = "./assets/sprites/apple.png";
                break;
            case arcade::BlockType::GROUND:
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

    arcade::Event SDL2::pollEvent()
    {
        arcade::Event event;
        SDL_Event sdlEvent;

        event.pos = { 0, 0 };
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    event.bind = arcade::KeyBind::QUIT_EVENT;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    event.pos.x = sdlEvent.button.x;
                    event.pos.y = sdlEvent.button.y;
                    if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
                        event.bind = arcade::KeyBind::LEFT_MOUSE_KEY;
                    }
                    if (sdlEvent.button.button == SDL_BUTTON_RIGHT) {
                        event.bind = arcade::KeyBind::LEFT_MOUSE_KEY;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (sdlEvent.key.keysym.sym) {
                        case SDLK_a:
                            event.bind = arcade::KeyBind::A_KEY;
                            break;
                        case SDLK_b:
                            event.bind = arcade::KeyBind::B_KEY;
                            break;
                        case SDLK_c:
                            event.bind = arcade::KeyBind::C_KEY;
                            break;
                        case SDLK_d:
                            event.bind = arcade::KeyBind::D_KEY;
                            break;
                        case SDLK_e:
                            event.bind = arcade::KeyBind::E_KEY;
                            break;
                        case SDLK_f:
                            event.bind = arcade::KeyBind::F_KEY;
                            break;
                        case SDLK_g:
                            event.bind = arcade::KeyBind::G_KEY;
                            break;
                        case SDLK_h:
                            event.bind = arcade::KeyBind::H_KEY;
                            break;
                        case SDLK_i:
                            event.bind = arcade::KeyBind::I_KEY;
                            break;
                        case SDLK_j:
                            event.bind = arcade::KeyBind::J_KEY;
                            break;
                        case SDLK_k:
                            event.bind = arcade::KeyBind::K_KEY;
                            break;
                        case SDLK_l:
                            event.bind = arcade::KeyBind::L_KEY;
                            break;
                        case SDLK_m:
                            event.bind = arcade::KeyBind::M_KEY;
                            break;
                        case SDLK_n:
                            event.bind = arcade::KeyBind::N_KEY;
                            break;
                        case SDLK_o:
                            event.bind = arcade::KeyBind::O_KEY;
                            break;
                        case SDLK_p:
                            event.bind = arcade::KeyBind::P_KEY;
                            break;
                        case SDLK_q:
                            event.bind = arcade::KeyBind::Q_KEY;
                            break;
                        case SDLK_r:
                            event.bind = arcade::KeyBind::R_KEY;
                            break;
                        case SDLK_s:
                            event.bind = arcade::KeyBind::S_KEY;
                            break;
                        case SDLK_t:
                            event.bind = arcade::KeyBind::T_KEY;
                            break;
                        case SDLK_u:
                            event.bind = arcade::KeyBind::U_KEY;
                            break;
                        case SDLK_v:
                            event.bind = arcade::KeyBind::V_KEY;
                            break;
                        case SDLK_w:
                            event.bind = arcade::KeyBind::W_KEY;
                            break;
                        case SDLK_x:
                            event.bind = arcade::KeyBind::X_KEY;
                            break;
                        case SDLK_y:
                            event.bind = arcade::KeyBind::Y_KEY;
                            break;
                        case SDLK_z:
                            event.bind = arcade::KeyBind::Z_KEY;
                            break;
                        case SDLK_0:
                            event.bind = arcade::KeyBind::NUM0_KEY;
                            break;
                        case SDLK_1:
                            event.bind = arcade::KeyBind::NUM1_KEY;
                            break;
                        case SDLK_2:
                            event.bind = arcade::KeyBind::NUM2_KEY;
                            break;
                        case SDLK_3:
                            event.bind = arcade::KeyBind::NUM3_KEY;
                            break;
                        case SDLK_4:
                            event.bind = arcade::KeyBind::NUM4_KEY;
                            break;
                        case SDLK_5:
                            event.bind = arcade::KeyBind::NUM5_KEY;
                            break;
                        case SDLK_6:
                            event.bind = arcade::KeyBind::NUM6_KEY;
                            break;
                        case SDLK_7:
                            event.bind = arcade::KeyBind::NUM7_KEY;
                            break;
                        case SDLK_8:
                            event.bind = arcade::KeyBind::NUM8_KEY;
                            break;
                        case SDLK_9:
                            event.bind = arcade::KeyBind::NUM9_KEY;
                            break;
                        case SDLK_LEFT:
                            event.bind = arcade::KeyBind::LEFT_KEY;
                            break;
                        case SDLK_RIGHT:
                            event.bind = arcade::KeyBind::RIGHT_KEY;
                            break;
                        case SDLK_UP:
                            event.bind = arcade::KeyBind::UP_KEY;
                            break;
                        case SDLK_DOWN:
                            event.bind = arcade::KeyBind::DOWN_KEY;
                            break;
                        case SDLK_RETURN:
                            event.bind = arcade::KeyBind::ENTER_KEY;
                            break;
                        case SDLK_SPACE:
                            event.bind = arcade::KeyBind::SPACE_KEY;
                            break;
                        case SDLK_ESCAPE:
                            event.bind = arcade::KeyBind::ESCAPE_KEY;
                            break;
                        case SDLK_BACKSPACE:
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
        return std::make_unique<arcade::SDL2>().release();
    }
}
