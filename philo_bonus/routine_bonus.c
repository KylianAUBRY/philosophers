/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:27:04 by kylian            #+#    #+#             */
/*   Updated: 2023/08/12 11:59:39 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_eat(t_philo *temp)
{
	t_philo	*philo;

	philo = temp;
	sem_wait(philo->inf->forks);
	usleep(100);
	sem_wait(philo->inf->forks);
	sem_wait(philo->inf->time);
	if (gettimeofday(&philo->time_last_eat, NULL) == -1)
	{
		sem_post(philo->inf->time);
		return (print_error_message(ERRCODE_GETTIME));
	}
	++philo->nb_eat;
	sem_post(philo->inf->time);
	ft_print(philo, "is eating\n");
	usleep(philo->inf->time_eat * 1000);
	sem_post(philo->inf->forks);
	sem_post(philo->inf->forks);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping\n");
	usleep(philo->inf->time_sleep * 1000);
	ft_print(philo, "is thinking\n");
	return (0);
}

int	ft_verif_2(t_philo *philo)
{
	sem_wait(philo->inf->time);
	if (philo->inf->nb_time_eat != -1
		&& philo->nb_eat > philo->inf->nb_time_eat)
	{
		sem_post(philo->inf->time);
		sem_wait(philo->inf->print);
		printf("%ldms the philosophers are satiated\n",
			get_time(philo->inf->start_time));
		sem_post(philo->inf->print);
		sem_post(philo->inf->stop);
		return (1);
	}
	sem_post(philo->inf->time);
	return (0);
}

void	*ft_verif(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	while (1)
	{
		sem_wait(philo->inf->time);
		if (get_time(philo->time_last_eat) > philo->inf->time_die)
		{
			sem_post(philo->inf->time);
			sem_wait(philo->inf->print);
			printf("%ldms %d die\n", get_time(philo->inf->start_time),
				philo->id);
			sem_post(philo->inf->print);
			sem_post(philo->inf->stop);
			break ;
		}
		sem_post(philo->inf->time);
		if (ft_verif_2(philo) == 1)
			break ;
	}
	return (NULL);
}

void	ft_routine(t_philo *philo)
{
	pthread_t	death;

	if (philo->id % 2 == 0)
		usleep(1000);
	if (gettimeofday(&philo->time_last_eat, NULL) == -1)
	{
		sem_wait(philo->inf->print);
		print_error_message(ERRCODE_GETTIME);
		sem_post(philo->inf->stop);
		return ;
	}
	pthread_create(&death, NULL, ft_verif, philo);
	pthread_detach(death);
	while (1)
	{
		if (ft_eat(philo) != 0)
			return ;
		if (ft_sleep(philo) != 0)
			return ;
	}
	sem_post(philo->inf->stop);
}
