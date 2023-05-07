/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:49:28 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/06 12:03:00 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_errors(char **av)
{
	int		y;
	long	x;

	y = 0;
	if (ft_atoi(av[1]) > 200)
	{
		printf("Error\n no more than 200 thread allowed\n");
		return (1);
	}
	while (av[++y])
	{
		if (!ft_isdigit(av[y]) || !ft_strlen(av[y]))
		{
			printf("Error\nonly digit\n");
			return (1);
		}
		x = ft_atoi(av[y]);
		if (x < 0 || x > INT_MAX)
		{
			printf("Error\nno negative allowed\nno more than max int\n");
			return (1);
		}
	}
	return (0);
}

int	check_all_ate(t_philo *phil)
{
	if (phil->vars->nbr_to_eat != -1)
	{
		if (phil->vars->all_ate == phil->vars->nbr_philo)
		{
			pthread_mutex_unlock(&phil->vars->check);
			return (1);
		}
	}
	return (0);
}

int	fill_struct(char **av, t_list *va)
{
	va->nbr_philo = ft_atoi(av[1]);
	va->time_to_die = ft_atoi(av[2]);
	va->time_to_eat = ft_atoi(av[3]);
	va->time_to_slp = ft_atoi(av[4]);
	if (av[5])
	{
		va->nbr_to_eat = ft_atoi(av[5]);
		if (va->nbr_to_eat == 0)
			return (0);
	}
	else
		va->nbr_to_eat = -1;
	return (0);
}
