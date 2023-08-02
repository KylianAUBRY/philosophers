/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:53:32 by kylian            #+#    #+#             */
/*   Updated: 2023/08/02 17:17:46 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
