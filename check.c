#include "philo.h"

int	err_msg(char *error_msg)
{
	printf("%s\n", error_msg);
	return(1);
}

int check_args(t_args *args, char **argv)
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
				return(err_msg("Invalid arguments\n"));
			j++;
		}
		i++;
	}
	return (0);
}

int checker(t_args *args, t_philo *philo)
{
	int	i;
	// usleep(2000000);
	while (1)
	{
		i = -1;
		while (++i < args->all)
		{
			pthread_mutex_lock(&philo->args->mutex);
			if (((get_time_now() - philo[i].last_meal)) * 1000 > args->tt_die)
			{
				// printf("time now %llu\n", get_time_now());
				// printf("time passed %llu\n", (get_time_now() - philo[i].last_meal) * 1000);
				// printf("ttdie %d\n",args->tt_die);
				// printf("a%d\n",philo[i].last_meal);
				pthread_mutex_unlock(&philo->args->mutex);
				pthread_mutex_lock(&args->print_lock);
				// printf("time nowfgdfg %llu\n", args->start);
				printf("%llu %d %s\n", get_time_now() - args->start, philo[i].name, "has died :'((");
				return (1);
			}
			if (args->meals == 0)
			{
				pthread_mutex_unlock(&philo->args->mutex);
				return (1);
			}
			pthread_mutex_unlock(&philo->args->mutex);
		}
	}
	return (0);
}

// void test_print(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->args->print_lock);
// 	printf("%d %llu\n", philo->name, philo->last_meal);
// 	printf("%llu\n", philo->args->tt_die);
// 	pthread_mutex_unlock(&philo->args->print_lock);
// }


// int checker(t_args *args, t_philo *philo)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < args->all)
// 	{
// 		pthread_mutex_lock(&args->checker);
// 		if (is_dead(args, &philo[i]))
// 			return (1);
// 		if (args->meals == 0)
// 			return (1);
// 		pthread_mutex_unlock(&args->checker);
// 	}
// }