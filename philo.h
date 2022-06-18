#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t t_mutex;
typedef struct s_philo t_philo;
typedef struct s_args t_args;

struct s_philo
{
	int					name;
	int					left;
	int					right;
	int					count_meals;
	unsigned long long	last_meal;
	pthread_t			t_id;
	t_args 				*args;
	t_mutex				*forks;
	// int				flag_fork;
};

struct s_args
{
	int					all;
	int					tt_die;
	int					tt_eat;
	int					tt_sleep;
	int					meals; //argv[5]
	// int count_fed_up ?
	unsigned long long	start;
	t_mutex				*forks;
	t_mutex				print_lock;
	t_mutex				mutex;
	t_philo				*philo;
};


#endif
