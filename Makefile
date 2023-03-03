CC= gcc -g
NAME=philo
CFLAGS= -Wall -Werror -Wextra
SRC= main.c
OBJ=$(SRC:.c=.o)


all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFTA) -o $(NAME)


clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME)


re:

.PHONY: libft