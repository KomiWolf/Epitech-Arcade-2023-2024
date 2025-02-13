## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

CXX    =    g++

RM    =    rm -rf

LDFLAGS    =    -ldl

CXXFLAGS    =    -Wall -Wextra -fPIC -shared -fno-gnu-unique

CPPFLAGS    =    -iquote ../../include

# Ncurses
NCURSES_SRC    =    ./Ncurses.cpp \
					./NcursesWrapper.cpp \

NCURSES_OBJ    =    $(NCURSES_SRC:.cpp=.o)

NCURSES_FLAGS    =    -lncurses

NCURSES_NAME    =    arcade_ncurses.so

# SDL
SDL_SRC    =    ./SDL2.cpp

SDL_OBJ    =    $(SDL_SRC:.cpp=.o)

SDL_FLAGS    =    -lSDL2 -lSDL2_ttf -lSDL2_image

SDL_NAME    =    arcade_sdl2.so

# SFML
SFML_SRC    =    ./SFML.cpp

SFML_OBJ    =    $(SFML_SRC:.cpp=.o)

SFML_FLAGS    =    -lsfml-graphics -lsfml-window -lsfml-system

SFML_NAME    =    arcade_sfml.so

all: sfml sdl ncurses

sdl:	$(SDL_OBJ)
		$(CXX) $(LDFLAGS) $(SDL_OBJ) -o $(SDL_NAME) $(SDL_FLAGS) $(CXXFLAGS)
		mv $(SDL_NAME) ../../lib/

sfml:	$(SFML_OBJ)
		$(CXX) $(LDFLAGS) $(SFML_OBJ) -o $(SFML_NAME) $(SFML_FLAGS) $(CXXFLAGS)
		mv $(SFML_NAME) ../../lib/

ncurses: $(NCURSES_OBJ)
		$(CXX) $(LDFLAGS) $(NCURSES_OBJ) -o $(NCURSES_NAME) $(NCURSES_FLAGS) $(CXXFLAGS)
		mv $(NCURSES_NAME) ../../lib/

clean:
		$(RM) $(SDL_OBJ)
		$(RM) $(SFML_OBJ)
		$(RM) $(NCURSES_OBJ)

fclean: clean
		$(RM) ../../lib/$(SDL_NAME)
		$(RM) ../../lib/$(SFML_NAME)
		$(RM) ../../lib/$(NCURSES_NAME)

re:		fclean all

debug:	CFLAGS += -g3
debug:	clean all

.PHONY:	all sfml clean fclean re debug sdl
