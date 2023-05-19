/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:03:02 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/19 12:06:21 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	died(t_philo *phil)
{
	sem_wait(phil->vars->writing);
	phil->stop = 1;
	sem_post(phil->vars->writing);
	sem_wait(phil->vars->writing);
	printf("%ld %d died\n", timing() - phil->vars->time_at_start, \
	phil->id_philo + 1);
	sem_post(phil->vars->check);
	exit (2);
}

static void	*the_watcher(void *data)
{
	t_philo	*phil;

	phil = (t_philo *)data;
	while (1)
	{
		sem_wait(phil->vars->check);
		if (phil->vars->nbr_to_eat != -1)
		{
			sem_wait(phil->vars->check_death);
			if (phil->ate == phil->vars->nbr_to_eat)
			{
				sem_post(phil->vars->check_death);
				sem_post(phil->vars->check);
				exit (5);
			}
			sem_post(phil->vars->check_death);
		}
		if ((int)(timing() - phil->last_meal) >= phil->vars->time_to_die)
			died(phil);
		sem_post(phil->vars->check);
	}
	return (NULL);
}

static void	philosopher(t_philo *phil)
{
	pthread_create(&phil->thread, NULL, the_watcher, phil);
	pthread_detach(phil->thread);
	while (1)
	{
		printing("is thinking", phil);
		sem_wait(phil->vars->fork);
		printing("has taken a fork", phil);
		sem_wait(phil->vars->fork);
		printing("has taken a fork", phil);
		sem_wait(phil->vars->check);
		phil->last_meal = timing();
		sem_post(phil->vars->check);
		printing("is eating", phil);
		my_sleep(phil->vars->time_to_eat);
		sem_wait(phil->vars->check_death);
		phil->ate++;
		sem_post(phil->vars->check_death);
		sem_post(phil->vars->fork);
		sem_post(phil->vars->fork);
		printing("is sleeping", phil);
		my_sleep(phil->vars->time_to_slp);
	}
}

static int	start(t_list *va)
{
	int	i;

	i = 0;
	va->time_at_start = timing();
	while (i < va->nbr_philo)
	{
		va->phil[i].last_meal = timing();
		va->pid[i] = fork();
		if (va->pid[i] == -1)
			return (1);
		if (va->pid[i] == 0)
			philosopher(&va->phil[i]);
		i++;
	}
	wait_for_childs(va, i);
	free_all(va, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_list	va;

	if (ac != 5 && ac != 6)
		write(2, "wrong args", 10);
	else
	{
		if (check_errors(av) || fill_struct(av, &va) \
			|| allocation(&va) || initialisation(&va) \
			|| start(&va))
			return (1);
	}
	return (0);
}
