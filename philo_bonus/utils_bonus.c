/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:23:55 by kylian            #+#    #+#             */
/*   Updated: 2023/08/08 20:24:08 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long int	ft_atol(const char *nptr)
{
	long		i;
	long		neg;
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
