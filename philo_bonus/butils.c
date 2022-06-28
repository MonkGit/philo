/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   butils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaree <slaree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:14:06 by slaree            #+#    #+#             */
/*   Updated: 2022/06/28 21:14:48 by slaree           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bphilo.h"

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

int	err_msg(char *error_msg)
{
	if (!error_msg)
		return (1);
	while (*error_msg)
	{
		write(2, error_msg, 1);
		error_msg++;
	}
	exit(EXIT_FAILURE);
}

void	print_msg(t_args *args, t_philo *philo, char *msg)
{
	int			name;
	long long	s_time;

	name = philo->name;
	s_time = args->start;
	sem_wait(args->print_lock);
	printf("%llu %d %s\n", get_time_now() - s_time, name, msg);
	sem_post(args->print_lock);
}
