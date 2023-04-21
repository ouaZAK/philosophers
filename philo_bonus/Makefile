CC = cc
FLAGS = -Wall -Wextra -Werror
NAME_BNS = philo_bonus
RM = rm -rf
SRC_BNS = 	main_bonus.c \
			alloc_and_free_bonus.c \
			check_and_fill_bonus.c \
			init_bonus.c \
			utils_bonus.c

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