#include "philo.h"

int	return_error(char *error_msg)
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
				return(return_error("Invalid arguments\n"));
			j++;
		}
		i++;
	}
	return (0);
}