/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adieux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:19:08 by kylian            #+#    #+#             */
/*   Updated: 2023/08/02 19:18:39 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_adieux_mutex_time(t_philo **philo, t_info **info, int i)
{
	t_philo	*temp;
	int		j;

	j = 0;
	temp = *philo;
	while (temp != NULL && j < i)
	{
		pthread_mutex_destroy(&temp->time);
		temp = temp->next;
		j++;
	}
	pthread_mutex_destroy(&(*info)->print);
	ft_adieux_philo(*philo, *info);
	return (print_error_message(ERRCODE_MUTEX));
}

int	ft_adieux_philo(t_philo *philo, t_info *info)
{
	t_philo	*temp;

	temp = philo;
	while (temp != NULL)
	{
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
		free(temp);
		temp = philo;
	}
	pthread_mutex_destroy(&info->run);
	free(info);
	return (0);
}

int	ft_adieux_philo_malloc(t_philo *philo, t_info *info)
{
	t_philo	*temp;

	temp = philo;
	while (temp != NULL)
	{
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
		free(temp);
		temp = philo;
	}
	pthread_mutex_destroy(&info->run);
	free(info);
	return (print_error_message(ERRCODE_MALLOC));
}

int	ft_adieux_philo_mutex(t_philo *philo, t_info *info)
{
	t_philo	*temp;

	temp = philo;
	while (temp != NULL)
	{
		if (philo->next != NULL)
			pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
		free(temp);
		temp = philo;
	}
	pthread_mutex_destroy(&info->run);
	free(info);
	return (print_error_message(ERRCODE_MUTEX));
}

int	ft_adieux_create(t_philo **philo, t_info **info, int i)
{
	t_philo	*temp;
	int		j;

	j = 0;
	temp = *philo;
	pthread_mutex_lock(&(*info)->run);
	(*info)->running = -1;
	pthread_mutex_unlock(&(*info)->run);
	while (temp != NULL && j < i)
	{
		pthread_join(temp->tid, NULL);
		temp = temp->next;
		j++;
	}
	temp = *philo;
	while (temp != NULL)
	{
		pthread_mutex_destroy(&temp->time);
		temp = temp->next;
	}
	pthread_mutex_destroy(&(*info)->print);
	return (ft_adieux_philo(*philo, *info));
}
