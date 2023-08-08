/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:59:19 by kylian            #+#    #+#             */
/*   Updated: 2023/08/08 21:39:12 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/* ==================== error ==================== */

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
# define ERRCODE_SEM 8
# define ERRMSG_SEM "ERROR :\nSémaphore failed\n"
# define ERRCODE_PTHREAD 9
# define ERRMSG_PTHREAD "ERROR :\nStart pthread failed\n"
# define ERRCODE_FORK 10
# define ERRMSG_FORK "ERROR :\nStart fork failed\n"

/* ==================== include ==================== */

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>

/* ==================== structure ==================== */

typedef struct s_info
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_time_eat;
	struct timeval	start_time;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*stop;
	sem_t			*time;
}					t_info;

typedef struct s_philo
{
	int				nb_eat;
	int				id;
	pid_t			pid;
	struct timeval	time_last_eat;
	struct s_info	*inf;
	struct s_philo	*next;
}					t_philo;

/* ==================== function error ==================== */

int					print_error_message(int error_code);
int					ft_error_get_time(t_philo *philo);

/* ==================== function leave ==================== */

int					ft_adieux_fork(t_philo *philo, t_info *info, int i);
int					ft_adieux(t_philo *philo, t_info *info);
int					ft_adieux_routine(t_philo *philo, t_info *info);
int					ft_adieux_final(t_philo *philo, t_info *info);

/* ==================== function utils ==================== */

long int			ft_atol(const char *nptr);
int					ft_strlen(char *chaine);

/* ==================== function init arg ==================== */

int					ft_init_arg(t_info *info, int argc, char **argv);
int					ft_create_semaphores(t_info *info);

/* ==================== function process ==================== */

void				ft_routine(t_philo *philo);
int					ft_init_philo(t_info *info, t_philo **philo);

/* ==================== function print/time ==================== */

void				ft_print(t_philo *philo, char *chaine);
long				get_time(struct timeval start_time);

#endif