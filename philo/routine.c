/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:26:14 by kylian            #+#    #+#             */
/*   Updated: 2023/08/02 17:51:58 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		ft_print(philo, "has taken a fork left\n");
		pthread_mutex_lock(philo->fork_right);
		ft_print(philo, "has taken a fork right\n");
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		ft_print(philo, "has taken a fork right\n");
		pthread_mutex_lock(&philo->fork);
		ft_print(philo, "has taken a fork left\n");
	}
	return (0);
}

int	ft_satiated(t_philo *temp)
{
	t_philo	*philo;

	philo = temp;
	pthread_mutex_lock(&philo->inf->print);
	pthread_mutex_lock(&philo->inf->run);
	if (temp->inf->running != -1)
		printf("%ldms the philosophers are satiated\n",
			get_time(philo->inf->start_time));
	temp->inf->running = -1;
	pthread_mutex_unlock(&philo->inf->run);
	pthread_mutex_unlock(&philo->inf->print);
	return (1);
}

int	ft_eat(t_philo *temp)
{
	t_philo	*philo;

	philo = temp;
	ft_take_fork(philo);
	pthread_mutex_lock(&philo->time);
	if (gettimeofday(&philo->time_last_eat, NULL) == -1)
		return (ft_error_get_time(philo));
	pthread_mutex_unlock(&philo->time);
	ft_print(philo, "is eating\n");
	usleep(philo->inf->time_eat * 1000);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(&philo->fork);
	if (philo->inf->nb_time_eat != -1
		&& ++philo->nb_eat > philo->inf->nb_time_eat)
		return (ft_satiated(philo));
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping\n");
	usleep(philo->inf->time_sleep * 1000);
	ft_print(philo, "is thinking\n");
	return (0);
}

void	*thread_routine(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	pthread_mutex_lock(&philo->time);
	if (gettimeofday(&philo->time_last_eat, NULL) == -1)
	{
		pthread_mutex_lock(&philo->inf->run);
		philo->inf->running = -1;
		print_error_message(ERRCODE_GETTIME);
		pthread_mutex_unlock(&philo->inf->run);
		pthread_mutex_unlock(&philo->time);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->time);
	while (verif_run(philo) == 0)
	{
		if (ft_eat(philo) != 0)
			return (NULL);
		if (ft_sleep(philo) != 0)
			return (NULL);
	}
	return (NULL);
}
