/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:15:31 by kyaubry           #+#    #+#             */
/*   Updated: 2023/05/14 20:06:27 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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

typedef struct s_info
{
	int				argc;
	sem_t			*forks;
	sem_t			*message;
	sem_t			*stop;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_time_eat;

}					t_info;

typedef struct s_philo
{
	int				nb_eat;
	int				id;
	int				time_to_die;
	pid_t			pid;
	struct timeval	start_time;
	struct timeval	time_last_eat;
	struct s_info	*inf;
	struct s_philo	*next;
}					t_philo;

int					ft_nb_nbr(int n);
int					ft_atoi(const char *nptr);
int					ft_strlen(char *chaine);
long				get_time(struct timeval start_time);
void				ft_print(t_philo *philo, char *chaine);
void				ft_routine(t_philo *philo);
void				ft_create_semaphores(t_info *info);
void				ft_init_philo(t_info *info, t_philo **philo);
int					ft_init_arg(t_info *info, int argc, char **argv);
void				*ft_verif(void *temp);
void				ft_adieux(t_philo *philo, t_info *info);

#endif