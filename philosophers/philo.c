/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaree <slaree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:50:06 by slaree            #+#    #+#             */
/*   Updated: 2022/06/28 22:01:45 by slaree           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	process(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->right]);
	print_msg(philo->args, philo, "has taken a fork");
	pthread_mutex_lock(&philo->forks[philo->left]);
	print_msg(philo->args, philo, "has taken a fork");
	print_msg(philo->args, philo, "is eating");
	pthread_mutex_lock(&philo->args->meal_checker);
	if (philo->meal_n > 0)
		philo->meal_n--;
	pthread_mutex_unlock(&philo->args->meal_checker);
	pthread_mutex_lock(&philo->args->mutex);
	philo->last_meal = get_time_now();
	pthread_mutex_unlock(&philo->args->mutex);
	isleep(philo->args->tt_eat / 1000);
	pthread_mutex_unlock(&philo->forks[philo->left]);
	pthread_mutex_unlock(&philo->forks[philo->right]);
	print_msg(philo->args, philo, "is sleeping");
	isleep(philo->args->tt_sleep / 1000);
	print_msg(philo->args, philo, "is thinking");
}

void	*emulator(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->name % 2 == 0)
		usleep(200);
	while (1)
	{
		process(philo);
	}
}

int	create_threads(t_args *args, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < args->all)
	{
		if (pthread_create(&philo[i].t_id, NULL, emulator, &philo[i]) != 0)
			return (err_msg("Error occured while creating threads\n"));
		if (pthread_detach(philo[i].t_id) != 0)
			return (err_msg("The thread has not terminated\n"));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	*args;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (err_msg("Wrong number of arguments!\n"));
	args = malloc(sizeof(t_args));
	if (!args)
		return (err_msg("Malloc error\n"));
	if (fill_args(args, argv))
		return (1);
	philo = init_philo(args);
	if (!philo)
	{
		ft_free_destroy(args, philo);
		return (err_msg("Couldn't create philosophers\n"));
	}
	if (create_threads(args, philo))
		ft_free_destroy(args, philo);
	if (checker(args, philo))
		ft_free_destroy(args, philo);
	return (0);
}
