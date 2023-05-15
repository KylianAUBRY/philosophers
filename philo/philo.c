/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:06:18 by kyaubry           #+#    #+#             */
/*   Updated: 2023/05/15 16:41:29 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *chaine)
{
	pthread_mutex_lock(&philo->inf->print);
	if (philo->inf->running == -1)
	{
		pthread_mutex_unlock(&philo->inf->print);
		return ;
	}
	printf("%ldms %d %s", get_time(philo->start_time), philo->id, chaine);
	pthread_mutex_unlock(&philo->inf->print);
}

long	get_time(struct timeval start_time)
{
	static struct timeval	end_time;
	long					seconds;
	long					micro;

	gettimeofday(&end_time, NULL);
	seconds = end_time.tv_sec - start_time.tv_sec;
	micro = end_time.tv_usec - start_time.tv_usec;
	return ((seconds * 1000) + (micro / 1000));
}

void	*thread_routine(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	gettimeofday(&philo->time_last_eat, NULL);
	if (philo->id % 2 == 0)
		usleep(200);
	while (philo->inf->running != -1)
	{
		pthread_mutex_lock(&philo->fork);
		ft_print(philo, "has taken a fork left\n");
		pthread_mutex_lock(philo->fork_right);
		ft_print(philo, "has taken a fork right\n");
		ft_print(philo, "is eating\n");
		gettimeofday(&philo->time_last_eat, NULL);
		usleep(philo->inf->time_eat * 1000);
		philo->nb_eat++;
		gettimeofday(&philo->time_last_eat, NULL);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->fork_right);
		ft_print(philo, "is sleeping\n");
		usleep(philo->inf->time_sleep * 1000);
		ft_print(philo, "is thinking\n");
	}
	return (NULL);
}

int	start_pthread(t_philo **philo, t_info *info)
{
	t_philo			*temp;
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	temp = *philo;
	pthread_mutex_init(&info->print, NULL);
	while (temp != NULL)
	{
		temp->start_time = start_time;
		pthread_create(&temp->tid, NULL, thread_routine, (void *)temp);
		usleep(10);
		temp->nb_eat = 0;
		temp = temp->next;
	}
	return (1);
}

int	ft_init_philo(t_info *info, t_philo **philo)
{
	t_philo	*temp;
	t_philo	*temp2;
	int		i;

	i = 0;
	while (++i <= info->nb_philo)
	{
		temp = malloc(sizeof(t_philo) * 1);
		if (!temp)
			return (ft_adieux(*philo, info));
		temp->id = i;
		temp->time_to_die = info->time_die;
		temp->inf = info;
		temp->next = *philo;
		pthread_mutex_init(&temp->fork, NULL);
		if (i > 1)
			temp->fork_right = &(*philo)->fork;
		else
			temp2 = temp;
		*philo = temp;
	}
	if (i > 1)
		temp2->fork_right = &(*philo)->fork;
	return (start_pthread(philo, info));
}
