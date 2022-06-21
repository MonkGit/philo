/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaree <slaree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:42:02 by slaree            #+#    #+#             */
/*   Updated: 2022/06/21 18:30:39 by slaree           ###   ########.fr       */
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

void	print_msg(t_args *args, t_philo *philo, char *msg)
{
	int name;
	unsigned long long s_time;

	name = philo->name;
	s_time = args->start;
	pthread_mutex_lock(&args->print_lock);
	printf("%llu %d %s\n", get_time_now() - s_time, name, msg);
	pthread_mutex_unlock(&args->print_lock);	
}

void ft_free_destroy(t_args *args, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < args->all)
		pthread_mutex_destroy(&args->forks[i]);
	free(args->forks);
	pthread_mutex_destroy(&args->print_lock);
	pthread_mutex_destroy(&args->mutex);
	pthread_mutex_destroy(&args->meal_checker);
	free(args);
	free(philo);
}
