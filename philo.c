#include "philo.h"


// long long	ft_time(long long l)
// {
// 	struct timeval	t;

// 	gettimeofday(&t, NULL);
// 	l = 1;
// 	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
// }

// void	ft_sleep(long long t)
// {
// 	long long	b;

// 	b = ft_time(0);
// 	while (ft_time(0) < (b + t))
// 	{
// 		usleep(10);
// 	}
// }

// long long get_time_now(long long i)
// {
//     struct timeval	t;

// 	gettimeofday(&t, NULL);
//     i = 1;
// 	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
//     // struct timeval tv;
//     // long long time;

//     // if (gettimeofday(&tv, NULL) != 0)
//     //     return(err_msg("Gettimeofday error\n"));
//     // printf("gettime_func %lld\n", (tv.tv_sec * 1000 + tv.tv_usec / 1000));
//     // time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
//     // printf("time val = %lld\n", time);
//     // return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
//     // return (time);
// }

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

	i = -1;
	while(++i < args->all)
	{
		if(pthread_mutex_init(&args->forks[i], NULL) != 0)
			return(err_msg("Mutex error\n"));
	}
	if (pthread_mutex_init(&args->print_lock, NULL) != 0)
		return(err_msg("Mutex error\n"));
	if (pthread_mutex_init(&args->mutex, NULL) != 0)
		return(err_msg("Mutex error\n"));
	if (pthread_mutex_init(&args->meal_checker, NULL) != 0)
		return(err_msg("Mutex error\n"));
	return (0);
}

int	fill_args(t_args *args, char **argv)
{
	if (check_args(args, argv))
		return(1);
	args->start = get_time_now();
	args->all = ft_atoi(argv[1]);
	args->tt_die = ft_atoi(argv[2]) * 1000;
	args->tt_eat = ft_atoi(argv[3]) * 1000;
	args->tt_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
	{
		args->meals = ft_atoi(argv[5]);
		if (args->meals < 1)
			return(err_msg("Parameters are out of range\n"));
	}
	else
		args->meals = -1;
	if (args->all > 200 || args-> tt_die < 1
		 || args ->tt_eat < 1 || args->tt_sleep < 1)
		 return(err_msg("Parameters are out of range\n"));
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
	philo = malloc(sizeof(t_philo) * args->all);
	if (!philo)
		return (NULL);
	while (++i < args->all)
	{
		philo[i].args = args;
		philo[i].name = i + 1;
		// philo[i].count_meals = 0;
		philo[i].last_meal = args->start;
		// printf("philo[%d] last meal %lld\n", i, philo[i].last_meal);
		philo[i].right = i;
		philo[i].left = i + 1;
		if (args->all == 1)
		{
			philo[i].left = 0;
			return (0);
		}
		if (philo[i].name == args->all)
		{
			philo[i].right = 0;
			philo[i].left = i;
		}
		philo[i].forks = args->forks;
		if (args->meals > 0)
			philo[i].meal_n = args->meals + 1;
		else
			philo[i].meal_n = -1;
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
	pthread_mutex_lock(&philo->args->meal_checker);
	if (philo->meal_n  > 0)
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
			return (err_msg("Error occured while creating threads\n"));
		if (pthread_detach(philo[i].t_id) != 0)
			return (err_msg("The thread has not terminated\n"));
	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_args *args;
	t_philo *philo;
	if (argc < 5 || argc > 6)
		return(err_msg("Wrong number of arguments!"));
	if (!(args = malloc(sizeof(t_args))))
		return (err_msg("Malloc error"));
	if (fill_args(args, argv))
		return (1);
	philo = init_philo(args);
	if (!philo)
		return(err_msg("Couldn't create philosophers"));
	// int i = -1;
	// while (++i < args->all)
	// {
	// 	printf("name %d, left fork %d, right fork %d ", philo[i].name, philo[i].left, philo[i].right);
	// 	printf("last meal %llu tt_eat %llu\n", philo[i].last_meal, args->tt_eat);
	// }
	create_threads(args, philo);
	if (checker(args, philo) == 1)
		ft_free_destroy(args, philo);
	return (0);
}