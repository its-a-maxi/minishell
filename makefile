# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/17 12:56:13 by alejandro         #+#    #+#              #
#    Updated: 2020/10/14 10:16:49 by aleon-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = src/*.c

NAME = minishell
INCLUDE = inc/
FLAGS = -Werror -Wextra -Wall
GCC = gcc $(FLAGS) -I $(INCLUDE) -framework CoreFoundation

LIB_PATH = libft/
LIB_FLAGS = -L $(LIB_PATH) -lft
LIB1 = libft.a

RM = rm -f

$(NAME):
	make -C $(LIB_PATH)
	$(GCC) $(LIB_FLAGS) $(SRCS) -o $(NAME)

all:		$(NAME)

clean:
	make clean -C $(LIB_PATH)

fclean:		clean
	make fclean -C $(LIB_PATH)
	$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
