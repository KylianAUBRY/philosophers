/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:58:10 by kyaubry           #+#    #+#             */
/*   Updated: 2023/05/13 21:35:23 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info
{
	int				running;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_time_eat;
	pthread_mutex_t	print;
}					t_info;

typedef struct s_philo
{
	int				nb_eat;
	int				id;
	int				time_to_die;
	struct timeval	time_befor_eat;
	struct timeval	time_last_eat;
	struct s_info	*inf;
	struct timeval	start_time;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_right;
	pthread_t		tid;
	struct s_philo	*next;
}					t_philo;

void				ft_putchar(char c);
void				ft_putstr(char *s);
int					ft_nb_nbr(int n);
int					ft_atoi(const char *nptr);
int					ft_strlen(char *chaine);
int					ft_uno(t_info *info);
long				get_time(struct timeval start_time);
void				ft_init_philo(t_info *info, t_philo **philo);
int					start_pthread(t_philo **philo);
void				*thread_routine(void *temp);
long				get_time(struct timeval start_time);
void				ft_print(t_philo *philo, char *chaine);
int					ft_init_arg(t_info *info, int argc, char **argv);
int					ft_adieux(t_philo *philo, t_info *info);
int					ft_verif_eat(t_philo *philo, t_info *info);
int					ft_verif(t_philo *philo, t_info *info, int argc);

#endif