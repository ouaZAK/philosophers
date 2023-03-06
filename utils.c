/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:04:54 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/03/06 08:56:58 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	res;
	long	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

long long	timing(t_list *va)
{
	(void)va;
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
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
