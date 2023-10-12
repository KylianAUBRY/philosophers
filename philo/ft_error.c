/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:20:51 by kylian            #+#    #+#             */
/*   Updated: 2023/08/02 19:18:42 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_get_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->inf->run);
	print_error_message(ERRCODE_GETTIME);
	philo->time_last_eat.tv_usec += 9999;
	philo->time_last_eat.tv_usec += 9999;
	philo->inf->running = -1;
	pthread_mutex_unlock(&philo->inf->run);
	pthread_mutex_unlock(&philo->time);
	return (0);
}

void	ft_print_error(char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		write(2, &src[i], 1);
}

int	print_error_message(int error_code)
{
	if (error_code == ERRCODE_MALLOC)
		ft_print_error(ERRMSG_MALLOC);
	else if (error_code == ERRCODE_MANY_ARG)
		ft_print_error(ERRMSG_MANY_ARG);
	else if (error_code == ERRCODE_ARG)
		ft_print_error(ERRMSG_ARG);
	else if (error_code == ERRCODE_ARG_NEG)
		ft_print_error(ERRMSG_ARG_NEG);
	else if (error_code == ERRCODE_ARG_INT)
		ft_print_error(ERRMSG_ARG_INT);
	else if (error_code == ERRCODE_ARG_NUMBER)
		ft_print_error(ERRMSG_ARG_NUMBER);
	else if (error_code == ERRCODE_GETTIME)
		ft_print_error(ERRMSG_GETTIME);
	else if (error_code == ERRCODE_MUTEX)
		ft_print_error(ERRMSG_MUTEX);
	else if (error_code == ERRCODE_PTHREAD)
		ft_print_error(ERRMSG_PTHREAD);
	return (1);
}
