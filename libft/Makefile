SRCS	= src/*.c

OBJS	= $(SRCS:.c=.o)

INCLUDE = include/

FLAGS	= -Werror -Wall -Wextra -I $(INCLUDE)

NAME	= libft.a

RM		= rm -f

$(NAME):
		gcc $(FLAGS) -c $(SRCS)
		mv *.o src/
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

all:	$(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re bonus
