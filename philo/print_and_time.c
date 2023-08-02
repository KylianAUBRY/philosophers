/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:35:20 by kylian            #+#    #+#             */
/*   Updated: 2023/08/02 19:23:50 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(struct timeval start_time)
{
	static struct timeval	end_time;
	long					seconds;
	long					micro;

	if (gettimeofday(&end_time, NULL) == -1)
	{
		print_error_message(ERRCODE_GETTIME);
		return (99999999);
	}
	seconds = end_time.tv_sec - start_time.tv_sec;
	micro = end_time.tv_usec - start_time.tv_usec;
	return ((seconds * 1000) + (micro / 1000));
}

int	verif_run(t_philo *philo)
{
	pthread_mutex_lock(&philo->inf->run);
	if (philo->inf->running == -1)
	{
		pthread_mutex_unlock(&philo->inf->run);
		return (1);
	}
	pthread_mutex_unlock(&philo->inf->run);
	return (0);
}

void	ft_print(t_philo *philo, char *chaine)
{
	pthread_mutex_lock(&philo->inf->print);
	pthread_mutex_lock(&philo->inf->run);
	if (philo->inf->running == 0)
		printf("%ldms %d %s", get_time(philo->inf->start_time), philo->id,
			chaine);
	pthread_mutex_unlock(&philo->inf->run);
	pthread_mutex_unlock(&philo->inf->print);
}
