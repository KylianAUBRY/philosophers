/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:18:34 by kyaubry           #+#    #+#             */
/*   Updated: 2023/05/15 16:31:10 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_arg(t_info *info, int argc, char **argv)
{
	info->nb_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		info->nb_time_eat = ft_atoi(argv[5]);
		if (ft_nb_nbr(info->nb_time_eat) != ft_strlen(argv[5]))
		{
			free(info);
			return (0);
		}
	}
	if (ft_nb_nbr(info->nb_philo) != ft_strlen(argv[1])
		|| ft_nb_nbr(info->time_die) != ft_strlen(argv[2])
		|| ft_nb_nbr(info->time_eat) != ft_strlen(argv[3])
		|| ft_nb_nbr(info->time_sleep) != ft_strlen(argv[4]))
	{
		free(info);
		return (0);
	}
	if (info->nb_philo == 1)
		return (ft_uno(info));
	return (1);
}

int	ft_adieux(t_philo *philo, t_info *info)
{
	t_philo	*temp;

	temp = philo;
	if (info)
		info->running = -1;
	while (temp != NULL)
	{
		pthread_join(temp->tid, NULL);
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
		free(temp);
		temp = philo;
	}
	pthread_mutex_destroy(&info->print);
	if (info)
		free(info);
	return (0);
}

int	ft_verif_eat(t_philo *philo, t_info *info)
{
	t_philo	*temp;

	temp = philo;
	while (temp != NULL)
	{
		if (temp->nb_eat < info->nb_time_eat)
			return (0);
		temp = temp->next;
	}
	temp = philo;
	pthread_mutex_lock(&temp->inf->print);
	printf("%ldms the philosophers are satiated\n",
		get_time(temp->start_time));
	info->running = -1;
	pthread_mutex_unlock(&temp->inf->print);
	ft_adieux(philo, info);
	return (1);
}

int	ft_verif(t_philo *philo, t_info *info, int argc)
{
	t_philo	*temp;

	temp = philo;
	while (1)
	{
		if (get_time(temp->time_last_eat) > temp->time_to_die)
		{
			info->running = -1;
			pthread_mutex_lock(&temp->inf->print);
			printf("%ldms %d die\n", get_time(temp->start_time), philo->id);
			info->running = -1;
			pthread_mutex_unlock(&temp->inf->print);
			ft_adieux(philo, info);
			return (0);
		}
		if (argc == 6 && ft_verif_eat(philo, info) == 1)
			return (0);
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
	if (argc != 6 && argc != 5)
		return (0);
	info = malloc(sizeof(t_info) * 1);
	if (!info)
		return (0);
	if (ft_init_arg(info, argc, argv) == 0)
		return (0);
	info->running = 1;
	if (ft_init_philo(info, &philo) == 0)
		return (0);
	usleep(200);
	return (ft_verif(philo, info, argc));
}
