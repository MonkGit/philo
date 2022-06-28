/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bchecks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaree <slaree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:14:57 by slaree            #+#    #+#             */
/*   Updated: 2022/06/28 21:28:55 by slaree           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bphilo.h"

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

static void	print_death(t_args *args, long long t)
{
	sem_wait(args->deathprint);
	printf("%lld %d %s\n", (get_time_now() - t), (args->pi + 1), "died");
}

void	*checker(void *data)
{
	t_args		*args;
	long long	t;

	args = (t_args *)data;
	while (1)
	{
		sem_wait(args->checker);
		t = time_to_long(args->philo[args->pi].last_meal);
		sem_post(args->checker);
		if (args->tt_die < (get_time_now() - t) * 1000)
		{
			sem_wait(args->print_lock);
			print_death(args, t);
			exit(0);
		}
		isleep(2);
	}
}
