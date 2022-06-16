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

t_philo	*init_philo(t_args *args)
{
	int i;
	t_philo *philo;

	i = -1;
	if (!(philo = malloc(sizeof(t_philo) * args->all)))
		return (return_error("Malloc problems\n"));
	args->start = get_time_now();
	while (++i < args->all)
	{
		philo[i].name = i + 1;
		philo[i].count_meals = 0;
		philo[i].last_meal = args->start;
		philo[i].right = i;
		if (args->all == 1)
		{
			philo[i].left = 0;
			return (0);
		}
		if (philo[i].name == args->all)
			philo[i].right = 0;
		philo[i].left = i + 1;
		philo[i].args = args;
		philo[i].forks = args->forks;
	}
	return (philo);
}

void process(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->right]);
	print_msg(philo->args, philo, "has taken a fork");
	pthread_mutex_lock(&philo->forks[philo->left]);
	print_msg(philo->args, philo, "has taken a fork");
	print_msg(philo->args, philo, "is eating");
	isleep(philo->args->tt_eat / 1000);
	pthread_mutex_unlock(&philo->forks[philo->left]);
	pthread_mutex_unlock(&philo->forks[philo->right]);
}

void *emulator(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->name % 2 == 0)
		usleep(100);
	while (1)
	{
		process(philo);
	}
}

int	create_threads(t_args *args, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < args->all)
	{
		if (pthread_create(&philo[i].t_id, NULL, emulator, &philo[i]) != 0)
			return (return_error("Error occured while creating threads\n"));
		if (pthread_detach(philo[i].t_id) != 0)
			return (return_error("The thread has not terminated\n"));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args args;
	t_philo *philo;
	if (argc < 5 || argc > 6)
		return(return_error("Wrong number of arguments!"));
	if (fill_args(&args, argv))
		return (1);
	philo = init_philo(&args);
	//if (!philo)
	create_threads(&args, philo);
	usleep(90000000);
	
	
	
	// int i = -1;
	// while (++i < args.all)
	// 	printf("%d\n", philo[i].args->all);
	// 	printf("NAME %d,left fork %d, right fork %d ATE %d times, LAST MEAL %llu\n",args.philo[i].name, args.philo[i].left, args.philo[i].right, args.philo[i].count_meals, args.philo[i].last_meal);
	
	return (0);
}