/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bphilo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaree <slaree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:24:08 by slaree            #+#    #+#             */
/*   Updated: 2022/06/28 21:25:00 by slaree           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bphilo.h"

void	emulator(t_philo *philo, t_args *args)
{
	sem_post(args->print_lock);
	if (philo->name % 2 == 0)
		usleep(200);
	while (1)
	{
		if (philo->meal_n == 0 && philo->name == args->all)
			exit(0);
		sem_wait(args->forks);
		print_msg(args, philo, "has taken a fork");
		sem_wait(args->forks);
		print_msg(args, philo, "has taken a fork");
		print_msg(args, philo, "is eating");
		sem_wait(args->checker);
		gettimeofday(&philo->last_meal, NULL);
		sem_post(args->checker);
		isleep(args->tt_eat / 1000);
		sem_post(args->forks);
		sem_post(args->forks);
		if (philo->meal_n > 0)
			philo->meal_n--;
		print_msg(args, philo, "is sleeping");
		isleep(args->tt_sleep / 1000);
		print_msg(args, philo, "is thinking");
	}
}

void	create_threads(t_args *args, int i)
{
	t_philo	*philo;

	philo = &args->philo[i];
	args->pi = i;
	if (pthread_create(&args->philo[i].t_id, NULL, checker, args) != 0)
	{
		free(args);
		free(args->philo);
		err_msg("Error occured while creating threads\n");
	}
	if (pthread_detach(args->philo[i].t_id) != 0)
	{
		free(args);
		free(args->philo);
		err_msg("The thread has not terminated\n");
	}
	emulator(philo, args);
}

void	create_processes(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->all)
	{
		args->philo[i].pid = fork();
		if (args->philo[i].pid == -1)
			err_msg("Fork error\n");
		if (args->philo[i].pid == 0)
			create_threads(args, i);
	}
}

int	main(int argc, char **argv)
{
	t_args	*args;
	int		i;

	if (argc < 5 || argc > 6)
		return (err_msg("Wrong number of arguments!\n"));
	args = malloc(sizeof(t_args));
	if (!args)
		return (err_msg("Malloc error\n"));
	i = -1;
	b_fill_args(args, argv);
	init_semaphores(args);
	create_processes(args);
	waitpid(0, 0, 0);
	while (++i < args->all)
		kill(args->philo[i].pid, SIGTERM);
	ft_free_destroy(args, args->philo);
	return (0);
}
