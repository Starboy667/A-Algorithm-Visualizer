##
## EPITECH PROJECT, 2020
## delivery
## File description:
## Makefile
##

NAME = Pathfinder

SRC =	src/main.cpp		\
		src/pathfinder.cpp	\
		src/node.cpp

CFLAGS = -Wall -Werror -g3 -Iinclude -lsfml-graphics -lsfml-window -lsfml-system

all: $(NAME)


$(NAME): $(OBJ)
	g++ -o $(NAME) $(SRC) $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: lib