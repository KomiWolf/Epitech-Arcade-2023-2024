##
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

# Snake
SNAKE_SRC    =    ./Snake.cpp

SNAKE_OBJ    =    $(SNAKE_SRC:.cpp=.o)

SNAKE_NAME    =    arcade_snake.so

# Nibbler
NIBBLER_SRC    =    ./Nibbler.cpp

NIBBLER_OBJ    =    $(NIBBLER_SRC:.cpp=.o)

NIBBLER_NAME    =    arcade_nibbler.so

# Centipede
CENTIPEDE_SRC    =    ./Centipede.cpp

CENTIPEDE_OBJ    =    $(CENTIPEDE_SRC:.cpp=.o)

CENTIPEDE_NAME    =    arcade_centipede.so

all: snake nibbler

snake:  $(SNAKE_OBJ)
	$(CXX) $(LDFLAGS) $(SNAKE_OBJ) -o $(SNAKE_NAME) $(SNAKE_FLAGS) $(CXXFLAGS)
	mv $(SNAKE_NAME) ../../lib/

nibbler:  $(NIBBLER_OBJ)
	$(CXX) $(LDFLAGS) $(NIBBLER_OBJ) -o $(NIBBLER_NAME) $(NIBBLER_FLAGS) $(CXXFLAGS)
	mv $(NIBBLER_NAME) ../../lib/

centipede:  $(CENTIPEDE_OBJ)
	$(CXX) $(LDFLAGS) $(CENTIPEDE_OBJ) -o $(CENTIPEDE_NAME) $(CENTIPEDE_FLAGS) $(CXXFLAGS)
	mv $(CENTIPEDE_NAME) ../../lib/

clean:
	$(RM) $(SNAKE_OBJ)
	$(RM) $(NIBBLER_OBJ)
	$(RM) $(CENTIPEDE_OBJ)

fclean: clean
	$(RM) ../../lib/$(SNAKE_NAME)
	$(RM) ../../lib/$(NIBBLER_NAME)
	$(RM) ../../lib/$(CENTIPEDE_NAME)

re:		fclean all

debug:	CFLAGS += -g3
debug:	clean all

.PHONY:	all clean fclean re debug snake nibbler centipede
