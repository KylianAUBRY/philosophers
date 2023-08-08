/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_time_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:42:41 by kylian            #+#    #+#             */
/*   Updated: 2023/08/08 22:01:32 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_print(t_philo *philo, char *chaine)
{
	sem_wait(philo->inf->print);
	printf("%ldms %d %s", get_time(philo->inf->start_time), philo->id, chaine);
	sem_post(philo->inf->print);
}
