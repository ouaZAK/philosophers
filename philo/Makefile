CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = philo
RM = rm -rf
SRC =	main.c \
		utils.c \
		init.c \
		printing.c \
		alloc_and_free.c \
		check_and_fill.c \
		# list.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $^ -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all