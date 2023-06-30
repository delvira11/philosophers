CC= gcc -g
NAME=philo
CFLAGS= -Wall -Wextra -Werror
SRC= main.c routines.c inits.c simulation.c time_utils.c utils.c
OBJ=$(SRC:.c=.o)


all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFTA) -o $(NAME)


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)


re: fclean all

.PHONY: libft
