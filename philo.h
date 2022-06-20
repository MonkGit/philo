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
	// int					count_meals;
	long long	last_meal;
	int					meal_n;
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
	long long	start;
	t_mutex				*forks;
	t_mutex				print_lock;
	t_mutex				mutex;
	t_mutex				meal_checker;
	t_philo				*philo;
};

//time.c
long long get_time_now(void);
void isleep(long long ms);

//check.c
int	err_msg(char *error_msg);
int check_args(t_args *args, char **argv);
int checker(t_args *args, t_philo *philo);

//utils.c
int	ft_isdigit(char c);
int	ft_atoi(const char *str);
void	print_msg(t_args *args, t_philo *philo, char *msg);

//philo.c
int	init_mutex(t_args *args);
int	fill_args(t_args *args, char **argv);
t_philo	*init_philo(t_args *args);
void *emulator(void *data);
int	create_threads(t_args *args, t_philo *philo);


#endif
