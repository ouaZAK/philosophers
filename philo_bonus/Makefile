CC = cc
FLAGS = -Wall -Wextra -Werror
NAME_BNS = philo_bonus
RM = rm -rf
SRC_BNS = main.c

OBJ_BNS = $(SRC_BNS:.c=.o)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME_BNS)

$(NAME_BNS): $(OBJ_BNS)
	@$(CC) $(FLAGS) $^ -o $@

clean:
	@$(RM) $(OBJ_BNS)

fclean: clean
	@$(RM) $(NAME_BNS)

re: fclean all