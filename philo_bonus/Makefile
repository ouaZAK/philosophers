# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 15:02:39 by zouaraqa          #+#    #+#              #
#    Updated: 2023/06/12 09:38:28 by zouaraqa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror
NAME_BNS = philo_bonus
RM = rm -rf
SRC_BNS = 	init.c \
			main_bonus.c \
			utils_bonus.c \
			waiting_bonus.c \
			printing_bonus.c \
			alloc_and_free_bonus.c \
			check_and_fill_bonus.c

OBJ_BNS = $(SRC_BNS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME_BNS)

$(NAME_BNS): $(OBJ_BNS)
	$(CC) $(FLAGS) $^ -o $@

clean:
	@$(RM) $(OBJ_BNS)

fclean: clean
	@$(RM) $(NAME_BNS)

re: fclean all