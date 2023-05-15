/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:15:05 by kyaubry           #+#    #+#             */
/*   Updated: 2023/05/14 20:05:33 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	return (1);
}

void	*ft_verif(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	while (1)
	{
		if (get_time(philo->time_last_eat) > philo->time_to_die)
		{
			sem_wait(philo->inf->message);
			printf("%ldms %d die\n", get_time(philo->start_time), philo->id);
			sem_post(philo->inf->stop);
			break ;
		}
		if (philo->inf->argc == 6 && philo->nb_eat > philo->inf->nb_time_eat)
		{
			sem_wait(philo->inf->message);
			printf("%ldms the philosophers are satiated\n",
				get_time(philo->start_time));
			sem_post(philo->inf->stop);
			break ;
		}
	}
	return (NULL);
}

void	ft_adieux(t_philo *philo, t_info *info)
{
	t_philo	*temp;

	temp = philo;
	sem_close(info->message);
	sem_close(info->stop);
	sem_close(info->forks);
	free(info);
	while (temp != NULL)
	{
		philo = philo->next;
		free(temp);
		temp = philo;
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
	if (ft_init_arg(info, argc, argv) == 0)
		return (0);
	info->argc = argc;
	ft_create_semaphores(info);
	sem_wait(info->stop);
	ft_init_philo(info, &philo);
	sem_wait(info->stop);
	ft_adieux(philo, info);
	return (0);
}
