#include "philo.h"

void	check_errors(char **av)
{
	int		y;
	long	x;

	y = 0;
	if (ft_atoi(av[1]) > 200)
	{
		printf("Error\n no more than 200 thread allowed\n");
		exit(1);
	}
	while (av[++y])
	{
		if (!ft_isdigit(av[y]))
		{
			printf("Error\nonly digit\n");
			exit(1);
		}
		x = ft_atoi(av[y]);
		if (x < 0 || x > INT_MAX)
		{
			printf("Error\nno negative allowed\nno more than max int\n");
			exit(1);
		}
	}
}

void	fill_struct(char **av, t_list *va)
{
	va->nbr_philo = ft_atoi(av[1]);
	va->time_to_die = ft_atoi(av[2]);
	va->time_to_eat = ft_atoi(av[3]);
	va->time_to_slp = ft_atoi(av[4]);
	if (av[5])
	{
		va->nbr_to_eat = ft_atoi(av[5]);
		if (va->nbr_to_eat == 0)
			exit(0);
	}
	else
		va->nbr_to_eat = -1;
}
