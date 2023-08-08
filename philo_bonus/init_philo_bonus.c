/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:15:08 by kylian            #+#    #+#             */
/*   Updated: 2023/08/08 22:01:16 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	start_pros(t_philo **philo, t_info *info)
{
	t_philo	*temp;
	int		i;

	i = 0;
	temp = *philo;
	while (temp != NULL)
	{
		temp->nb_eat = 0;
		temp->pid = fork();
		usleep(10);
		if (temp->pid == -1)
		{
			ft_adieux_fork(*philo, info, i);
			return (print_error_message(ERRCODE_FORK));
		}
		if (temp->pid == 0)
		{
			ft_routine(temp);
			return (ft_adieux_routine(*philo, info));
		}
		temp = temp->next;
		i++;
	}
	return (0);
}

int	ft_init_philo(t_info *info, t_philo **philo)
{
	t_philo	*temp;
	int		i;

	i = 0;
	while (++i <= info->nb_philo)
	{
		temp = malloc(sizeof(t_philo) * 1);
		if (!temp)
		{
			ft_adieux(*philo, info);
			return (print_error_message(ERRCODE_MALLOC));
		}
		temp->id = i;
		temp->nb_eat = 0;
		temp->next = *philo;
		temp->inf = info;
		*philo = temp;
	}
	if (gettimeofday(&info->start_time, NULL) == -1)
	{
		ft_adieux(*philo, info);
		return (print_error_message(ERRCODE_GETTIME));
	}
	return (start_pros(philo, info));
}
