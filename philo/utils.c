/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:47:16 by kyaubry           #+#    #+#             */
/*   Updated: 2023/05/13 21:36:31 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_nb_nbr(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			neg;
	long long	nb;

	i = 0;
	neg = 1;
	nb = 0;
	while (((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ') && nptr[i])
		i++;
	if ((nptr[i] == '+' || nptr[i] == '-') && nptr[i])
	{
		if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9' && nptr[i])
	{
		nb = (nb * 10) + (nptr[i] - '0');
		i++;
	}
	return (neg * nb);
}

int	ft_strlen(char *chaine)
{
	int	i;

	i = 0;
	while (chaine[i])
		i++;
	return (i);
}

int	ft_uno(t_info *info)
{
	printf("0ms 1 has taken a fork left\n");
	usleep(info->time_die * 1000);
	printf("%dms 1 die\n", info->time_die + 1);
	free(info);
	return (0);
}
