/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:15:43 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/03/04 17:45:21 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosofeur(void *data)
{
	t_list	*va;

	va = (t_list *)data;
	pthread_mutex_lock(&va->chopstick[va->id_philo]);
	printf("philo %d took fork\n", va->id_philo);
	pthread_mutex_lock(&va->chopstick[va->id_philo + 1]);
	printf("philo %d took fork\n", va->id_philo);
	printf("philo %d start eating\n", va->id_philo);
	// usleep(va->time_to_eat * 1000);
	pthread_mutex_unlock(&va->chopstick[va->id_philo + 1]);
	pthread_mutex_unlock(&va->chopstick[va->id_philo]);
	printf("philo %d start sleeping\n", va->id_philo);
	return (NULL);
}

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
		va->nbr_to_eat = 0;
}

void	initialisation(t_list *va)
{
	int	i;

	i = 1;
	while (i <= va->nbr_philo)
	{
		if (pthread_mutex_init(&va->chopstick[i++], NULL))
		{
			printf("Error\n");
			exit(1);
		}
	}
	i = 1;
	while (i <= va->nbr_philo)
	{
		va->id_philo = i;
		if (pthread_create(&va->philo[i++], NULL, philosofeur, va))
		{
			printf("Error\n");
			exit(1);
		}
		usleep(100);
	}
	i = 1;
	while (i <= va->nbr_philo)
	{
		if (pthread_join(va->philo[i++], NULL))
		{
			printf("Error\n");
			exit(1);
		}
	}
}

int	main(int ac, char **av)
{
	t_list	*va;

	va = malloc(sizeof(t_list));
	if (ac == 5 || ac == 6)
	{
		check_errors(av);
		fill_struct(av, va);
		initialisation(va);
	}
	else
		printf("wrong args\n");
	return (0);
}
