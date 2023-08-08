/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adieux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:17:10 by kylian            #+#    #+#             */
/*   Updated: 2023/08/08 22:01:03 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_adieux_routine(t_philo *philo, t_info *info)
{
	t_philo	*temp;

	temp = philo;
	free(info);
	while (temp != NULL)
	{
		philo = philo->next;
		free(temp);
		temp = philo;
	}
	exit(0);
	return (0);
}

int	ft_adieux_fork(t_philo *philo, t_info *info, int i)
{
	t_philo	*temp;
	int		j;

	j = 0;
	temp = philo;
	while (temp != NULL && j < i)
	{
		kill(philo->pid, SIGKILL);
		temp = temp->next;
		j++;
	}
	return (ft_adieux(philo, info));
}

int	ft_adieux_final(t_philo *philo, t_info *info)
{
	t_philo	*temp;

	temp = philo;
	while (temp != NULL)
	{
		kill(temp->pid, SIGKILL);
		temp = temp->next;
	}
	return (ft_adieux(philo, info));
}

int	ft_adieux(t_philo *philo, t_info *info)
{
	t_philo	*temp;

	temp = philo;
	while (temp != NULL)
	{
		philo = philo->next;
		free(temp);
		temp = philo;
	}
	sem_close(info->print);
	sem_close(info->stop);
	sem_close(info->forks);
	free(info);
	exit(0);
	return (0);
}
