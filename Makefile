##
## EPITECH PROJECT, 2021
## bootstrap_malloc
## File description:
## Makefile
##

CFLAGS	= -I./ -Wall -Wextra -fPIC -g

LNAME	=	my_malloc

NAME    =	lib$(LNAME).so

SRC		=	malloc.c \
			calloc.c \
			merge.c \
			reallocarray.c \
			blocks.c \


OBJS    =    $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	gcc -shared -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:		fclean all

run: 	re
	gcc main.c -L./ -l$(LNAME) -g