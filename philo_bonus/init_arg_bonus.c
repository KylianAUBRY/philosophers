/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:00:56 by kylian            #+#    #+#             */
/*   Updated: 2023/08/12 11:59:00 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_create_semaphores_2(t_info *info)
{
	info->time = sem_open("time", O_CREAT, 0600, 1);
	if (info->time == SEM_FAILED)
	{
		sem_close(info->forks);
		sem_close(info->print);
		sem_close(info->stop);
		return (print_error_message(ERRCODE_SEM));
	}
	return (0);
}

int	ft_create_semaphores(t_info *info)
{
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("stop");
	sem_unlink("time");
	info->print = sem_open("print", O_CREAT, 0600, 1);
	if (info->print == SEM_FAILED)
		return (print_error_message(ERRCODE_SEM));
	info->forks = sem_open("forks", O_CREAT, 0600, info->nb_philo);
	if (info->forks == SEM_FAILED)
	{
		sem_close(info->print);
		return (print_error_message(ERRCODE_SEM));
	}
	info->stop = sem_open("stop", O_CREAT, 0600, 1);
	if (info->stop == SEM_FAILED)
	{
		sem_close(info->forks);
		sem_close(info->print);
		return (print_error_message(ERRCODE_SEM));
	}
	return (ft_create_semaphores_2(info));
}

int	ft_verif_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		if (argv[i][0] == '-')
			return (print_error_message(ERRCODE_ARG_NEG));
		while (argv[i][j] == '0' && argv)
			j++;
		if (argv[i][j] == '\0')
			return (print_error_message(ERRCODE_ARG_NEG));
		if (ft_strlen(argv[i] + j) > 10)
			return (print_error_message(ERRCODE_ARG_INT));
		while (argv[i][j] >= '0' && argv[i][j] <= '9' && argv[i][j])
			j++;
		if (argv[i][j] != '\0')
			return (print_error_message(ERRCODE_ARG_NUMBER));
	}
	return (0);
}

int	ft_init_arg(t_info *info, int argc, char **argv)
{
	if (argc != 6 && argc != 5)
		return (print_error_message(ERRCODE_MANY_ARG));
	if (ft_verif_arg(argc, argv) == 1)
		return (1);
	info->nb_philo = ft_atol(argv[1]);
	info->time_die = ft_atol(argv[2]);
	info->time_eat = ft_atol(argv[3]);
	info->time_sleep = ft_atol(argv[4]);
	if (argc == 6)
		info->nb_time_eat = ft_atol(argv[5]);
	else
		info->nb_time_eat = -1;
	if (info->nb_philo > 2147483647 || info->time_die > 2147483647
		|| info->time_eat > 2147483647 || info->time_sleep > 2147483647
		|| info->nb_time_eat > 2147483647)
		return (print_error_message(ERRCODE_ARG_INT));
	return (0);
}
