/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:58:44 by kylian            #+#    #+#             */
/*   Updated: 2023/08/08 22:01:50 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_info	*info;
	t_philo	*philo;

	philo = NULL;
	info = malloc(sizeof(t_info) * 1);
	if (!info)
		return (print_error_message(ERRCODE_MALLOC));
	if (ft_init_arg(info, argc, argv) != 0 || ft_create_semaphores(info) != 0)
	{
		free(info);
		return (1);
	}
	sem_wait(info->stop);
	if (ft_init_philo(info, &philo) != 0)
		return (1);
	sem_wait(info->stop);
	ft_adieux_final(philo, info);
	return (0);
}
