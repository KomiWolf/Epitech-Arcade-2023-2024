# Arcade

## Which games we did ?
- Snake
- Nibbler

## Which graphical libraries we did ?
- Ncurses → Installation: `sudo dnf install ncurses ncurses-devel`
- SFML → Installation: `sudo dnf install SFML SFML-devel`
- SDL2 → Installation: `sudo dnf install SDL2 SDL2-devel SDL2_image SDL2_image-devel SDL2_ttf SDL2_ttf-devel`

## How to launch the program ?
1. Compile the program:
    - Compile everything: `make`
    - Compile only the core: `make core`
    - Compile only the graphical libraries: `make graphicals`
    - Compile only the games: `make games`
    - Clean the repository: `make clean`
    - Clean the entire repository: `make fclean`
    - Recompile the program: `make re`
2. Launch the program:
    - `./arcade ./lib/[graphical lib]`
        → graphical lib: It can be any graphical lib

## Where to put other libraries (Must to have the same architecture than us) ?
We have a "lib" folder, you need to put your games and graphical libraries inside it and it must be a ".so" file.

## The keyboard keys we handle
**General:**
- Up key → Go up
- Down key → Go down
- Left key → Go left
- Right key → Go right
- Escape key → Quit the program
- 8 key → Choose the previous graphical libraries
- 9 key → Choose the next graphical libraries

**Game only:**
- R key → Restart the game
- P key → Pause the game
- Enter key → Return to the selection menu

**Menu only:**
- Enter key → Confirm the game
- 1 key → Choose the previous game
- 2 key → Choose the next game
