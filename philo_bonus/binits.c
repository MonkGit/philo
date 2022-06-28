/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaree <slaree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:28:00 by slaree            #+#    #+#             */
/*   Updated: 2022/06/28 21:28:22 by slaree           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bphilo.h"

t_philo	*b_philo_init(t_args *args)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * args->all);
	if (!philo)
		return (NULL);
	while (++i < args->all)
	{
		philo[i].args = args;
		philo[i].name = i + 1;
		if (args->meals > 0)
			philo[i].meal_n = args->meals;
		else
			philo[i].meal_n = -1;
		gettimeofday(&philo[i].last_meal, NULL);
	}
	return (philo);
}

int	b_fill_args(t_args *args, char **argv)
{
	if (check_args(argv))
		return (1);
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
	if (args->all > 200 || args->all < 1 || args-> tt_die < 1
		|| args ->tt_eat < 1 || args->tt_sleep < 1)
		return (err_msg("Parameters are out of range\n"));
	args->start = get_time_now();
	args->philo = b_philo_init(args);
	if (!args->philo)
	{
		free(args);
		return (err_msg("Couldn't create philosophers\n"));
	}
	return (0);
}

void	init_semaphores(t_args *args)
{
	sem_unlink("forks");
	sem_unlink("printf_lock");
	sem_unlink("checker");
	sem_unlink("deathprint");
	args->forks = sem_open("forks", O_CREAT, S_IRWXU, args->all);
	if (args->forks == SEM_FAILED)
		err_msg("Couldn't create semaphores\n");
	args->print_lock = sem_open("print_lock", O_CREAT, S_IRWXU, 1);
	if (args->print_lock == SEM_FAILED)
		err_msg("Couldn't create semaphores\n");
	args->checker = sem_open("print_lock", O_CREAT, S_IRWXU, 1);
	if (args->checker == SEM_FAILED)
		err_msg("Couldn't create semaphores\n");
	args->deathprint = sem_open("deathprint", O_CREAT, S_IRWXU, 1);
	if (args->deathprint == SEM_FAILED)
		err_msg("Couldn't create semaphores\n");
}

void	ft_free_destroy(t_args *args, t_philo *philo)
{
	sem_unlink("forks");
	sem_unlink("printf_lock");
	sem_unlink("checker");
	sem_unlink("deathprint");
	sem_close(args->forks);
	sem_close(args->print_lock);
	sem_close(args->checker);
	sem_close(args->deathprint);
	free(args);
	free(philo);
	exit(0);
}
