/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:15:43 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/03/06 09:05:58 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosofeur(void *data)
{
	t_list	*va;

	va = (t_list *)data;
	if (va->id_philo % 2 == 0)
		usleep(100);
	va->time_at_start = timing(va);// time at start
	while (1)
	{
		// printf("%lld %d is thinking\n", timing(va), va->id_philo);
		pthread_mutex_lock(&va->chopstick[va->id_philo - 1]);
		pthread_mutex_lock(&va->chopstick[((va->id_philo - 1) % va->nbr_philo) + 1]);
		
		printf("%lld %d has taken a fork\n", timing(va), va->id_philo);
		//time now - time at start > ttd
		printf("%lld %d is eating\n", timing(va), va->id_philo);
		usleep(va->time_to_eat * 1000);
		
		pthread_mutex_unlock(&va->chopstick[((va->id_philo - 1) % va->nbr_philo) + 1]);
		pthread_mutex_unlock(&va->chopstick[va->id_philo - 1]);
		
		printf("%lld %d is sleeping\n", timing(va), va->id_philo);
		usleep(va->time_to_slp * 1000);
		printf("%lld %d is thinking\n", timing(va), va->id_philo);
	}
	return (NULL);
}

void	initialisation(t_list *va)
{
	int	i;

	i = 0;
	while (i < va->nbr_philo)
	{
		if (pthread_mutex_init(&va->chopstick[i++], NULL))
		{
			printf("Error\n");
			exit(1);
		}
	}
	i = 0;
	while (i < va->nbr_philo)
	{
		va->id_philo = i + 1;
		if (pthread_create(&va->philo[i++], NULL, philosofeur, va))
		{
			printf("Error\n");
			exit(1);
		}
		// usleep(100);
	}
	i = 0;
	while (i < va->nbr_philo)
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
