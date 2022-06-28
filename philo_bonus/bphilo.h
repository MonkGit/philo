/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bphilo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaree <slaree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:22:47 by slaree            #+#    #+#             */
/*   Updated: 2022/06/28 21:22:50 by slaree           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BPHILO_H
# define BPHILO_H

# include <semaphore.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;
typedef struct s_philo	t_philo;
typedef struct s_args	t_args;

struct s_args
{
	int			all;
	int			tt_die;
	int			tt_eat;
	int			tt_sleep;
	int			meals;
	long long	start;
	int			pi;
	sem_t		*forks;
	sem_t		*print_lock;
	sem_t		*checker;
	sem_t		*deathprint;
	t_philo		*philo;
};

struct s_philo
{
	int			name;
	pid_t		pid;
	t_timeval	last_meal;
	t_args		*args;
	pthread_t	t_id;
	int			meal_n;
};

// bphilo.c
void		create_processes(t_args *args);
void		create_threads(t_args *args, int i);
void		emulator(t_philo *philo, t_args *args);

// binits.c
int			b_fill_args(t_args *args, char **argv);
t_philo		*b_philo_init(t_args *args);
void		init_semaphores(t_args *args);
void		ft_free_destroy(t_args *args, t_philo *philo);

// bchecks.c
int			check_args(char **argv);
void		*checker(void *data);

// btime.c
long long	get_time_now(void);
void		isleep(long long ms);
long long	time_to_long(t_timeval t);

// butils.c
int			ft_isdigit(char c);
int			ft_atoi(const char *str);
int			err_msg(char *error_msg);
void		print_msg(t_args *args, t_philo *philo, char *msg);

#endif