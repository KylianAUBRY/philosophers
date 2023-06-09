/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 20:03:33 by kyaubry           #+#    #+#             */
/*   Updated: 2023/05/15 19:26:34 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print(t_philo *philo, char *chaine)
{
	sem_wait(philo->inf->message);
	printf("%ldms %d %s", get_time(philo->start_time), philo->id, chaine);
	sem_post(philo->inf->message);
}

void	ft_routine(t_philo *philo)
{
	pthread_t	death;

	if (philo->id % 2 == 0)
		usleep(500);
	gettimeofday(&philo->time_last_eat, NULL);
	pthread_create(&death, NULL, ft_verif, philo);
	pthread_detach(death);
	while (1)
	{
		sem_wait(philo->inf->forks);
		ft_print(philo, "has taken a fork 1\n");
		usleep(100);
		sem_wait(philo->inf->forks);
		ft_print(philo, "has taken a fork 2\n");
		ft_print(philo, "is eating\n");
		gettimeofday(&philo->time_last_eat, NULL);
		usleep(philo->inf->time_eat * 1000);
		philo->nb_eat++;
		sem_post(philo->inf->forks);
		sem_post(philo->inf->forks);
		ft_print(philo, "is sleeping\n");
		usleep((philo->inf->time_sleep * 1000));
		ft_print(philo, "is thinking\n");
	}
}

void	ft_create_semaphores(t_info *info)
{
	sem_unlink("message");
	sem_unlink("forks");
	sem_unlink("stop");
	info->message = sem_open("message", O_CREAT, 0600, 1);
	info->forks = sem_open("forks", O_CREAT, 0600, info->nb_philo);
	info->stop = sem_open("stop", O_CREAT, 0600, 1);
}

void	start_pros(t_philo **philo)
{
	t_philo			*temp;
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	temp = *philo;
	while (temp != NULL)
	{
		temp->nb_eat = 0;
		temp->start_time = start_time;
		temp->pid = fork();
		usleep(10);
		if (temp->pid == 0)
		{
			ft_routine(temp);
			exit(0);
		}
		temp = temp->next;
	}
}

void	ft_init_philo(t_info *info, t_philo **philo)
{
	t_philo	*temp;
	int		i;

	i = 0;
	while (++i <= info->nb_philo)
	{
		temp = malloc(sizeof(t_philo) * 1);
		if (!temp)
			ft_adieux(*philo, info);
		temp->id = i;
		temp->time_to_die = info->time_die;
		temp->next = *philo;
		temp->inf = info;
		*philo = temp;
	}
	start_pros(philo);
}
