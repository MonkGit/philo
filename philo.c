#include "philo.h"

long long	get_time(void)
{
	struct timeval time;
	long long posix_time;

	gettimeofday(&time, NULL);
	posix_time = time.tv_sec * 1000LL + time.tv_usec / 1000;
	return (posix_time);
}

void	init_philo_args(t_args *args, char **argv)
{
	args->number_of_philosophers = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		args->must_eat = atoi(argv[5]);
	else
		args->must_eat = 0;
}

int	main(int argc, char **argv)
{
	
	// printf("Number of philosophers is %d\n", PHT_SIZE);
	return (0);
}