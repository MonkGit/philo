/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaree <slaree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:42:02 by slaree            #+#    #+#             */
/*   Updated: 2022/06/13 16:07:18 by slaree           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}


int	ft_atoi(const char *str)
{
	int			sign;
	long int	nb;
	long int	tmp;

	sign = 1;
	nb = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		tmp = nb;
		nb = nb * 10 + (*str++ - '0');
		if ((tmp < 0 && nb > 0) || (tmp > 0 && nb < 0))
			return ((sign == 1) * -1);
	}
	return (nb * sign);
}
