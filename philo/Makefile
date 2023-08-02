NAME	=	philo

SRCS	=	main.c	\
			utils.c \
			routine.c \
			ft_error.c \
			ft_uno.c \
			init_philo.c \
			init_arg.c \
			ft_adieux.c \
			print_and_time.c \
		
OBJ =	${SRCS:.c=.o}

CC =	cc

CFLAGS	=	-Wall -Wextra -Werror -pthread -g -fsanitize=thread # -fsanitize=address

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