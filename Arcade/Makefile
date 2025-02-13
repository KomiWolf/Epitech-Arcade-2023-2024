##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

CC	=	g++

RM	=	rm -rf

SRC	=	./main.cpp \
\
		./src/ExceptionHandling.cpp \
		./src/ArgsHandler.cpp \
\
		./src/core/Core.cpp \
		./src/core/LibraryLoader.cpp \

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -fno-gnu-unique

CPPFLAGS	=	-iquote ./include

NAME	=	arcade

all: 		core games graphicals

core:		$(OBJ)
	$(CC) $(OBJ) -o $(NAME)

games:
	make -C ./src/games all

graphicals:
	make -C ./src/graphicals all

clean:
	$(RM) $(OBJ)
	make -C ./src/graphicals clean
	make -C ./src/games clean

fclean: 	clean
	$(RM) $(NAME)
	make -C ./src/graphicals fclean
	make -C ./src/games fclean

re:	fclean all
	make -C ./src/graphicals re
	make -C ./src/games re

debug:	CFLAGS += -g3
debug:	clean all
	make -C ./src/graphicals debug
	make -C ./src/games debug

.PHONY:	all clean fclean re debug core graphicals games
