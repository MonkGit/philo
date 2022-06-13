#include "philo.h"


// long long	get_time(void)
// {
// 	struct timeval time;
// 	long long posix_time;

// 	gettimeofday(&time, NULL);
// 	posix_time = time.tv_sec * 1000LL + time.tv_usec / 1000;
// 	return (posix_time);
// }

int	init_mutex(t_args *args)
{
	int i;

	i = 0;
	while(++i < args->all)
	{
		if(pthread_mutex_init(&args->forks[i], NULL) != 0)
			return(return_error("Mutex error\n"));
	}
	if (pthread_mutex_init(&args->print_lock, NULL) != 0)
		return(return_error("Mutex error\n"));
	return (0);
}

int	fill_args(t_args *args, char **argv)
{
	if (check_args(args, argv))
		return(1);
	args->all = ft_atoi(argv[1]);
	
	args->tt_die = ft_atoi(argv[2]) * 1000;
	args->tt_eat = ft_atoi(argv[3]) * 1000;
	args->tt_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
	{
		args->meals = ft_atoi(argv[5]);
		if (args->meals < 1)
			return(return_error("Parameters are out of range\n"));
	}
	else
		args->meals = -1;
	if (args->all > 200 || args-> tt_die < 1
		 || args ->tt_eat < 1 || args->tt_sleep < 1)
		 return(return_error("Parameters are out of range\n"));
	args->forks = malloc(sizeof(t_mutex) * args->all);
	if (!args->forks)
		return (1);
	if (init_mutex(args) != 0)
		return (1);
	return (0);
}

int	init_philo(t_args *args)
{
	int i;

	i = -1;
	args->philo = malloc(sizeof(t_philo) * args->all);
	if (!args->philo)
		return (return_error("Malloc problems\n"));
	args->start = get_time_now();
	while (++i < args->all)
	{
		args->philo[i].name = i + 1;
		args->philo[i].count_meals = 0;
		args->philo[i].last_meal = args->start;
		args->philo[i].right = i;
		if (args->all == 1)
		{
			args->philo[i].left = 0;
			return (0);
		}
		if (args->philo[i].name == args->all)
			args->philo[i].right = 0;
		args->philo[i].left = i + 1;
	//pthread_mutex_init(&p[i].eating, 0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args args;
	// if (argc < 5 || argc > 6)
	// 	return(return_error("Wrong number of arguments!"));
	if (fill_args(&args, argv))
		return (1);
	init_philo(&args);

	printf("%llu\n", args.start);
	int i = -1;
	// while (++i < args.all)
	// 	printf("NAME %d,left fork %d, right fork %d ATE %d times, LAST MEAL %llu\n",args.philo[i].name, args.philo[i].left, args.philo[i].right, args.philo[i].count_meals, args.philo[i].last_meal);
	
	return (0);
}