/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaree <slaree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:58:00 by slaree            #+#    #+#             */
/*   Updated: 2022/06/28 21:58:33 by slaree           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->all)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			return (err_msg("Mutex error\n"));
	}
	if (pthread_mutex_init(&args->print_lock, NULL) != 0)
		return (err_msg("Mutex error\n"));
	if (pthread_mutex_init(&args->mutex, NULL) != 0)
		return (err_msg("Mutex error\n"));
	if (pthread_mutex_init(&args->meal_checker, NULL) != 0)
		return (err_msg("Mutex error\n"));
	return (0);
}

int	fill_args(t_args *args, char **argv)
{
	if (check_args(argv))
		return (1);
	args->start = get_time_now();
	args->all = ft_atoi(argv[1]);
	args->tt_die = ft_atoi(argv[2]) * 1000;
	args->tt_eat = ft_atoi(argv[3]) * 1000;
	args->tt_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
	{
		args->meals = ft_atoi(argv[5]);
		if (args->meals < 1)
			return (err_msg("Parameters are out of range\n"));
	}
	else
		args->meals = -1;
	if (args->all > 200 || args->all < 1 || args->tt_die < 1
		|| args->tt_eat < 1 || args->tt_sleep < 1)
		return (err_msg("Parameters are out of range\n"));
	args->forks = malloc(sizeof(t_mutex) * args->all);
	if (!args->forks)
		return (1);
	if (init_mutex(args) != 0)
		return (1);
	return (0);
}

static void	check_meal(t_args *args, t_philo *philo, int i)
{
	if (args->meals > 0)
		philo[i].meal_n = args->meals + 1;
	else
		philo[i].meal_n = -1;
}

t_philo	*init_philo(t_args *args)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = malloc(sizeof(t_philo) * args->all);
	if (!philo)
		return (NULL);
	while (++i < args->all)
	{
		philo[i].args = args;
		philo[i].name = i + 1;
		philo[i].last_meal = args->start;
		philo[i].right = i;
		philo[i].left = i + 1;
		if (args->all == 1)
			philo[i].left = 0;
		if (philo[i].name == args->all)
		{
			philo[i].right = i;
			philo[i].left = 0;
		}
		philo[i].forks = args->forks;
		check_meal(args, philo, i);
	}
	return (philo);
}
