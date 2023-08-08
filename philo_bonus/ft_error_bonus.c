/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:01:45 by kylian            #+#    #+#             */
/*   Updated: 2023/08/08 20:21:05 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	else if (error_code == ERRCODE_SEM)
		ft_print_error(ERRMSG_SEM);
	else if (error_code == ERRCODE_PTHREAD)
		ft_print_error(ERRMSG_PTHREAD);
	else if (error_code == ERRCODE_FORK)
		ft_print_error(ERRMSG_FORK);
	return (1);
}
