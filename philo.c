#include "philo.h"
void	return_error(char *error_msg)
{
	printf("%s\n", error_msg);
	exit(EXIT_FAILURE);
}

// long long	get_time(void)
// {
// 	struct timeval time;
// 	long long posix_time;

// 	gettimeofday(&time, NULL);
// 	posix_time = time.tv_sec * 1000LL + time.tv_usec / 1000;
// 	return (posix_time);
// }

void	init_params(t_args *args, char **argv)
{
	args->number_of_philosophers = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	// args->starting_point = get_time();
	if (argv[5])
	{
		args->number_of_meals = atoi(argv[5]);
		//if(args->number_of_meals < 1)
			// return_error("Invalid parameters");
	}
	else
		args->number_of_meals = 0;
}

int	init_philosophers(t_args *args)
{
	int	i;

	i = 0;
	gettimeofday(&args->start, NULL);
	while (i < args->number_of_philosophers)
	{
		args->philo[i].id = i;
		args->philo[i].right_fork = (args->number_of_philosophers - 1) - i;
		args->philo[i].left_fork = i;
		args->philo[i].args = args;
		//args->philo[i].last_meal = args->start;
		i++;
	}
	return (0);
}

void	init_mutex(t_args *args)
{
	int i;

	i = 0;
	if (pthread_mutex_init(&args->breaker, NULL) != 0)
		return_error("Mutex_init error");
	if (pthread_mutex_init(&args->print_lock, NULL) != 0)
		return_error("Mutex_init error");
	while (i < args->number_of_philosophers)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			return_error("Mutex_init error");
		i++;
	}
}
int	main(int argc, char **argv)
{
	t_args args;
	// if (argc < 5 || argc > 6)
	// 	return_error("Wrong number of arduments!");
	//validation of parameters
	// init_params(&args,argv);	
	// gettimeofday(args.start, NULL);

	return (0);
}