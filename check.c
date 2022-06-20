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
	int n;
	int flag = -1;
	while (1)
	{
		i = -1;
		while (++i < args->all)
		{
			// pthread_mutex_lock(&philo[i].args->print_lock);
			// printf("yime_now %lld\n",get_time_now());
			// printf("time passed %lld\n",get_time_now() - args->start);
			// pthread_mutex_unlock(&philo[i].args->print_lock);
			pthread_mutex_lock(&philo->args->mutex);
			if ((get_time_now() - philo[i].last_meal) * 1000 > args->tt_die)
			{
				// printf("time now %llu\n", get_time_now());
				// printf("time passed %llu\n", (get_time_now() - philo[i].last_meal) * 1000);
				// printf("ttdie %d\n",args->tt_die);
				// printf("a%lld\n",philo[i].last_meal);
				pthread_mutex_unlock(&philo->args->mutex);
				pthread_mutex_lock(&args->print_lock);
				// printf("time nowfgdfg %llu\n", args->start);
				printf("%llu %d %s\n", get_time_now() - args->start, philo[i].name, "has died :'((");
				return (1);
			}
			pthread_mutex_lock(&philo->args->meal_checker);
			n = -1;
			while(++n < args->all)
			{
				if (philo->meal_n == 0)
					flag = 1;
				else
					flag = -1;
			}
			pthread_mutex_unlock(&philo->args->meal_checker);
			if (flag == 1)
			{
				pthread_mutex_lock(&args->print_lock);
				pthread_mutex_unlock(&philo->args->mutex);
				return (1);
			}
			pthread_mutex_unlock(&philo->args->mutex);
		}
	}
	return (0);
}