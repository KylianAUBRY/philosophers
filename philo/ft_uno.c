/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uno.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:49:50 by kylian            #+#    #+#             */
/*   Updated: 2023/08/02 19:18:46 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_uno_routine(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	pthread_mutex_lock(&philo->fork);
	printf("0ms 1 has taken a fork left\n");
	usleep(philo->inf->time_die * 1000);
	printf("%dms 1 die\n", philo->inf->time_die + 1);
	pthread_mutex_unlock(&philo->fork);
	return (NULL);
}

int	ft_uno(t_info *info)
{
	t_philo	*temp;

	temp = malloc(sizeof(t_philo) * 1);
	if (!temp)
	{
		free(info);
		return (print_error_message(ERRCODE_MALLOC));
	}
	temp->inf = info;
	if (pthread_mutex_init(&temp->fork, NULL) == 0)
	{
		if (pthread_create(&temp->tid, NULL, thread_uno_routine,
				(void *)temp) == 0)
			pthread_join(temp->tid, NULL);
		else
			print_error_message(ERRCODE_PTHREAD);
		pthread_mutex_destroy(&temp->fork);
	}
	else
		print_error_message(ERRCODE_MUTEX);
	pthread_mutex_destroy(&info->run);
	free(info);
	free(temp);
	return (0);
}
