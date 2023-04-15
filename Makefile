CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = philo
RM = rm -rf
SRC =	main.c \
		utils.c \
		printing.c \
		# list.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $^ -o $@
# -fsanitize=thread -g 
clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all