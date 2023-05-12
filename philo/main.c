/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:49:46 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/12 15:58:16 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop(t_philo *phil)
{
	if (phil->vars->nbr_philo != -1)
	{
		pthread_mutex_lock(&phil->vars->check);
		if (phil->ate == phil->vars->nbr_to_eat)
		{
			phil->vars->all_ate++;
			pthread_mutex_unlock(&phil->vars->check);
			return (1);
		}
		pthread_mutex_unlock(&phil->vars->check);
	}
	pthread_mutex_lock(&phil->vars->check_dead);
	if (phil->vars->stop == 1)
	{
		pthread_mutex_unlock(&phil->vars->check_dead);
		return (1);
	}
	pthread_mutex_unlock(&phil->vars->check_dead);
	return (0);
}

void	*philosofeur(void *data)
{
	t_philo	*va;

	va = (t_philo *)data;
	if ((va->id_philo + 1) % 2 == 0)
		usleep(100);
	while (1)
	{
		if (check_stop(va))
			return (NULL);
		printing("is thinking\n", va);
		taking_forks(va);
		pthread_mutex_lock(&va->vars->check);
		va->time_last_meal = timing();
		pthread_mutex_unlock(&va->vars->check);
		eating(va);
		sleeping(va);
		pthread_mutex_lock(&va->vars->check);
		va->ate++;
		pthread_mutex_unlock(&va->vars->check);
	}
	return (NULL);
}

void	ihdiyay(t_philo *phil)
{
	int	i;

	i = 0;
	while (1)
	{
		i = -1;
		while (++i < phil->vars->nbr_philo)
		{
			pthread_mutex_lock(&phil->vars->check);
			if (check_all_ate(phil))
				return ;
			if (((int)(timing() - phil[i].time_last_meal) >= \
				phil->vars->time_to_die) \
				&& phil[i].ate != phil->vars->nbr_to_eat)
			{
				died(phil);
				return ;
			}
			pthread_mutex_unlock(&phil->vars->check);
		}
	}
	return ;
}

int	start(t_list *va)
{
	int	i;

	i = 0;
	while (i < va->nbr_philo)
	{
		va->phil[i].time_last_meal = timing();
		if (pthread_create(&va->phil[i].thread, NULL, \
			philosofeur, &va->phil[i]))
			if (exit_free_msg(va, "Error\nin create thread\n", 2))
				return (1);
		usleep(50);
		i++;
	}
	i = 0;
	ihdiyay(va->phil);
	if (va->nbr_philo == 1)
		pthread_mutex_unlock(&va->fork[0]);
	exit_free_msg(va, NULL, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_list	va;

	if (ac != 5 && ac != 6)
		printf("wrong args\n");
	else
	{
		if (check_errors(av) || fill_struct(av, &va) \
			|| allocation(&va) || initialisation(&va) \
			|| start(&va))
			return (1);
	}
	return (0);
}
