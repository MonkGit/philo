#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meals;
	// long long starting_point;
	struct timeval *start;
	pthread_mutex_t forks[200];
	t_philo			philo[200];
	pthread_mutex_t	breaker;
	pthread_mutex_t	print_lock;
}	t_args;

typedef struct s_philo
{
	int id;
	int	left_fork;
	int	right_fork;
	// int				flag_fork;
	// int				count_eat;
	// struct timeval last_meal;
	t_args *args;
	pthread_t	thread_id;
}	t_philo;

#endif
