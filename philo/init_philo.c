/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:12:11 by kylian            #+#    #+#             */
/*   Updated: 2023/08/02 19:19:20 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_pthread(t_philo **philo, t_info *info)
{
	t_philo	*temp;
	int		i;

	i = 0;
	temp = *philo;
	while (temp != NULL)
	{
		if (pthread_create(&temp->tid, NULL, thread_routine, (void *)temp) != 0)
		{
			ft_adieux_create(philo, &info, i);
			return (print_error_message(ERRCODE_PTHREAD));
		}
		usleep(1000);
		temp = temp->next;
		i++;
	}
	return (0);
}

int	ft_init_and_start(t_philo **philo, t_info **info)
{
	t_philo			*temp;
	struct timeval	start_time;
	int				i;

	i = 0;
	if (gettimeofday(&start_time, NULL) == -1)
	{
		ft_adieux_philo(*philo, *info);
		return (print_error_message(ERRCODE_GETTIME));
	}
	temp = *philo;
	if (pthread_mutex_init(&(*info)->print, NULL) != 0)
	{
		ft_adieux_philo(*philo, *info);
		return (print_error_message(ERRCODE_MUTEX));
	}
	(*info)->start_time = start_time;
	while (temp != NULL)
	{
		if (pthread_mutex_init(&temp->time, NULL) != 0)
			return (ft_adieux_mutex_time(philo, info, i));
		i++;
		temp = temp->next;
	}
	return (start_pthread(philo, *info));
}

int	ft_init_philo(t_info **info, t_philo **philo)
{
	t_philo	*temp;
	t_philo	*temp2;
	int		i;

	i = 0;
	while (++i <= (*info)->nb_philo)
	{
		temp = malloc(sizeof(t_philo) * 1);
		if (!temp)
			return (ft_adieux_philo_malloc(*philo, *info));
		temp->id = i;
		temp->nb_eat = 0;
		temp->inf = *info;
		temp->next = *philo;
		if (pthread_mutex_init(&temp->fork, NULL) != 0)
			return (ft_adieux_philo_mutex(temp, *info));
		if (i > 1)
			temp->fork_right = &(*philo)->fork;
		else
			temp2 = temp;
		*philo = temp;
	}
	if (i > 1)
		temp2->fork_right = &(*philo)->fork;
	return (ft_init_and_start(philo, info));
}
