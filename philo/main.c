/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:49:46 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/06/13 12:38:48 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_stop(t_philo *phil)
{
	if (phil->vars->nbr_to_eat != -1)
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

static void	*philosopher(void *data)
{
	t_philo	*va;

	va = (t_philo *)data;
	printing("is thinking\n", va);
	if ((va->id_philo + 1) % 2 == 0)
		my_sleep(va->vars->time_to_eat / 2, va);
	while (1)
	{
		if (check_stop(va))
			return (NULL);
		taking_forks(va);
		pthread_mutex_lock(&va->vars->check);
		va->time_last_meal = timing();
		pthread_mutex_unlock(&va->vars->check);
		eating(va);
		pthread_mutex_lock(&va->vars->check);
		va->ate++;
		pthread_mutex_unlock(&va->vars->check);
		sleeping(va);
		printing("is thinking\n", va);
	}
	return (NULL);
}

static void	the_watcher(t_list *va)
{
	int	i;

	i = 0;
	while (1)
	{
		i = -1;
		while (++i < va->nbr_philo)
		{
			pthread_mutex_lock(&va->check);
			if (check_all_ate(va))
				return ;
			if (((int)(timing() - va->phil[i].time_last_meal) >= \
				va->time_to_die) \
				&& va->phil[i].ate != va->nbr_to_eat)
			{
				died(va, i);
				return ;
			}
			pthread_mutex_unlock(&va->check);
		}
	}
	return ;
}

static int	start(t_list *va)
{
	int	i;

	i = 0;
	while (i < va->nbr_philo)
	{
		va->phil[i].time_last_meal = timing();
		if (pthread_create(&va->phil[i].thread, NULL, \
			philosopher, &va->phil[i]))
			if (exit_free_msg(va, "Error\n", 2))
				return (1);
		i++;
	}
	i = 0;
	the_watcher(va);
	if (va->nbr_philo == 1)
		pthread_mutex_unlock(&va->fork[0]);
	exit_free_msg(va, NULL, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_list	va;

	if (ac != 5 && ac != 6)
		write(2, "wrong args\n", 11);
	else
	{
		if (check_errors(av) || fill_struct(av, &va) \
			|| allocation(&va) || initialisation(&va) \
			|| start(&va))
			return (1);
	}
	return (0);
}
