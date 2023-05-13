NAME	=	philo

SRCS	=	main.c	\
			utils.c \
			philo.c \
		

OBJ =	${SRCS:.c=.o}

CC =	cc

CFLAGS	=	-Wall -Wextra -Werror -pthread #-fsanitize=address

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): ${OBJ}
		$(CC) $(CFLAGS) -o $(NAME) ${OBJ}

all:	${NAME}

clean:
		rm -f ${OBJ}

fclean:	clean
		rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re