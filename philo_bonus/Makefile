NAME	=	philo_bonus

SRCS	=	main_bonus.c	\
			utils_bonus.c \
			ft_error_bonus.c \
			ft_adieux_bonus.c \
			init_philo_bonus.c \
			init_arg_bonus.c \
			routine_bonus.c \
			print_and_time_bonus.c\
		
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