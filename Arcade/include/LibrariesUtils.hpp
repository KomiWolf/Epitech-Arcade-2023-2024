/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-eric1.xu
** File description:
** Event
*/

#pragma once

namespace arcade
{
    // An enum class that refers to every handled key bind by the program
    enum class KeyBind {
        UNKNOWN,
        QUIT_EVENT,

        // Letters keys

        A_KEY,
        B_KEY,
        C_KEY,
        D_KEY,
        E_KEY,
        F_KEY,
        G_KEY,
        H_KEY,
        I_KEY,
        J_KEY,
        K_KEY,
        L_KEY,
        M_KEY,
        N_KEY,
        O_KEY,
        P_KEY,
        Q_KEY,
        R_KEY,
        S_KEY,
        T_KEY,
        U_KEY,
        V_KEY,
        W_KEY,
        X_KEY,
        Y_KEY,
        Z_KEY,

        // Num keys

        NUM0_KEY,
        NUM1_KEY,
        NUM2_KEY,
        NUM3_KEY,
        NUM4_KEY,
        NUM5_KEY,
        NUM6_KEY,
        NUM7_KEY,
        NUM8_KEY,
        NUM9_KEY,

        // Mouse keys

        LEFT_MOUSE_KEY,
        RIGHT_MOUSE_KEY,

        // Directional pad keys

        LEFT_KEY,
        RIGHT_KEY,
        UP_KEY,
        DOWN_KEY,

        // Other keys

        ENTER_KEY,
        SPACE_KEY,
        ESCAPE_KEY,
        BACKSPACE_KEY
    };

    // An enum class that refers to every block type available in the program
    enum class BlockType {
        UNKNOWN,

        // Generic to all games

        WALL,
        PLAYER,
        GROUND,

        // Snake + Nibbler

        APPLE,
        SNAKE_HEAD,
        SNAKE_BODY,
        SNAKE_TAIL,

        // Pacman

        DOTS,
        RED_GHOST,
        PINK_GHOST,
        BLUE_GHOST,
        YELLOW_GHOST,
        POWER_PELLETS,

        // Centipede

        SHOT,
        MUSHROOM,
        CENTIPEDE_HEAD,
        CENTIPEDE_BODY
    };

    // A generic structure that contains a position x and y
    struct Position {
        int x;
        int y;
    };

    // A generic enum class that contains every possible direction in 2 dimentions
    enum class Direction {
        NONE,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    // A generic structure that contains a key bind and a position for mouses event
    struct Event {
        arcade::KeyBind bind;
        Position pos; // For mouse event
    };

    /* A generic structure to store map data. It contains a block type,
    a position and a direction
    */
    struct MapData {
        arcade::BlockType type;
        arcade::Position pos;
        arcade::Direction direction;
    };
}
