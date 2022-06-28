/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaree <slaree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 22:04:18 by slaree            #+#    #+#             */
/*   Updated: 2022/06/28 22:17:00 by slaree           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_msg(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	return (1);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]))
				return (err_msg("Invalid arguments\n"));
			j++;
		}
		i++;
	}
	return (0);
}

int	check_meal(t_args *args, t_philo *philo)
{
	int	n;
	int	flag;

	pthread_mutex_lock(&philo->args->meal_checker);
	n = -1;
	flag = -1;
	while (++n < args->all)
	{
		if (philo[n].meal_n == 0)
			flag = 1;
		else
			flag = -1;
	}
	pthread_mutex_unlock(&philo->args->meal_checker);
	if (flag == 1)
	{
		pthread_mutex_lock(&args->print_lock);
		pthread_mutex_unlock(&philo->args->mutex);
		return (1);
	}
	return (0);
}

int	checker(t_args *args, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < args->all)
		{
			pthread_mutex_lock(&philo->args->mutex);
			if ((get_time_now() - philo[i].last_meal) * 1000 > args->tt_die)
			{
				pthread_mutex_unlock(&philo->args->mutex);
				pthread_mutex_lock(&args->print_lock);
				printf("%lld %d %s\n", get_time_now() - args->start,
					philo[i].name, "died");
				return (1);
			}
			if (check_meal(args, philo))
				return (1);
			pthread_mutex_unlock(&philo->args->mutex);
		}
	}
	return (0);
}
