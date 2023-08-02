/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:16:42 by kylian            #+#    #+#             */
/*   Updated: 2023/08/02 19:23:16 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_adieux(t_philo *philo, t_info *info)
{
	t_philo	*temp;

	temp = philo;
	while (temp != NULL)
	{
		pthread_join(temp->tid, NULL);
		pthread_mutex_destroy(&temp->time);
		temp = temp->next;
	}
	while (temp != NULL)
	{
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
		free(temp);
		temp = philo;
	}
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->run);
	free(info);
	return (0);
}

int	ft_verif(t_philo *philo, t_info *info)
{
	t_philo	*temp;

	temp = philo;
	while (1)
	{
		pthread_mutex_lock(&temp->time);
		if (get_time(temp->time_last_eat) > temp->inf->time_die)
		{
			pthread_mutex_lock(&philo->inf->print);
			pthread_mutex_lock(&philo->inf->run);
			if (info->running != -1)
				printf("%ldms %d die\n", get_time(temp->inf->start_time),
					temp->id);
			info->running = -1;
			pthread_mutex_unlock(&philo->inf->run);
			pthread_mutex_unlock(&philo->inf->print);
			pthread_mutex_unlock(&temp->time);
			return (ft_adieux(philo, info));
		}
		pthread_mutex_unlock(&temp->time);
		if (temp->next == NULL)
			temp = philo;
		else
			temp = temp->next;
	}
}

int	main(int argc, char **argv)
{
	t_info	*info;
	t_philo	*philo;

	philo = NULL;
	info = malloc(sizeof(t_info) * 1);
	if (!info)
		return (print_error_message(ERRCODE_MALLOC));
	if (ft_init_arg(info, argc, argv) != 0)
	{
		free(info);
		return (1);
	}
	info->running = 0;
	if (pthread_mutex_init(&info->run, NULL) != 0)
	{
		free(info);
		return (print_error_message(ERRCODE_MUTEX));
	}
	if (info->nb_philo == 1)
		return (ft_uno(info));
	if (ft_init_philo(&info, &philo) == 1)
		return (1);
	return (ft_verif(philo, info));
}
