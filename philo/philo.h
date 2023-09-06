/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:13:18 by kylian            #+#    #+#             */
/*   Updated: 2023/08/02 17:38:32 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ==================== error ==================== */

# define ERRCODE_ERR 0
# define ERRCODE_MALLOC 1
# define ERRMSG_MALLOC "ERROR :\nMalloc failed to allocate memory.\n"
# define ERRCODE_MANY_ARG 2
# define ERRMSG_MANY_ARG "ERROR :\nIt takes 4 or 5 arguments\n"
# define ERRCODE_ARG 3
# define ERRMSG_ARG "ERROR :\nARG are not good\n"
# define ERRCODE_ARG_NEG 4
# define ERRMSG_ARG_NEG "ERROR :\nOnly numbers greater than 0 are accepted\n"
# define ERRCODE_ARG_INT 5
# define ERRMSG_ARG_INT "ERROR :\nArguments must fit inside an int\n"
# define ERRCODE_ARG_NUMBER 6
# define ERRMSG_ARG_NUMBER "ERROR :\nArguments must only contain numbers\n"
# define ERRCODE_GETTIME 7
# define ERRMSG_GETTIME "ERROR :\nGettimeofday failed\n"
# define ERRCODE_MUTEX 8
# define ERRMSG_MUTEX "ERROR :\nMutex failed\n"
# define ERRCODE_PTHREAD 9
# define ERRMSG_PTHREAD "ERROR :\nStart pthread failed\n"

/* ==================== include ==================== */

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* ==================== structure ==================== */

typedef struct s_info
{
	int				running;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_time_eat;
	struct timeval	start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	run;
}					t_info;

typedef struct s_philo
{
	int				nb_eat;
	int				id;
	struct s_info	*inf;
	struct timeval	time_last_eat;
	pthread_mutex_t	time;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_right;
	pthread_t		tid;
	struct s_philo	*next;
}					t_philo;

/* ==================== function error ==================== */

int					print_error_message(int error_code);
int					ft_error_get_time(t_philo *philo);

/* ==================== function leave ==================== */

int					ft_adieux_create(t_philo **philo, t_info **info, int i);
int					ft_adieux_philo_mutex(t_philo *philo, t_info *info);
int					ft_adieux_philo_malloc(t_philo *philo, t_info *info);
int					ft_adieux_philo(t_philo *philo, t_info *info);
int					ft_adieux_mutex_time(t_philo **philo, t_info **info, int i);

/* ==================== function utils ==================== */

long int			ft_atol(const char *nptr);
int					ft_strlen(char *chaine);

/* ==================== function init arg ==================== */

int					ft_init_arg(t_info *info, int argc, char **argv);

/* ==================== function pthread ==================== */

int					ft_uno(t_info *info);
int					ft_init_philo(t_info **info, t_philo **philo);
void				*thread_routine(void *temp);

/* ==================== function print/time ==================== */

void				ft_print(t_philo *philo, char *chaine);
int					verif_run(t_philo *philo);
long				get_time(struct timeval start_time);

#endif
