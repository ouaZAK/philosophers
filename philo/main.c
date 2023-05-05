/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:15:43 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/05 11:32:17 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosofeur(void *data)
{
	t_philo	*va;

	va = (t_philo *)data;
	if ((va->id_philo + 1) % 2 == 0)
		usleep(100);
	while (1)
	{
		if (va->vars->nbr_philo != -1)
		{
			pthread_mutex_lock(&va->vars->check);
			if (va->ate == va->vars->nbr_to_eat)
			{
				va->vars->all_ate++;
				// printf("philo %d  ate = %d   all ate = %d\n", va->id_philo + 1, va->ate, va->vars->all_ate);
				pthread_mutex_unlock(&va->vars->check);
				return (NULL);
			}
			pthread_mutex_unlock(&va->vars->check);
		}
		
		pthread_mutex_lock(va->vars->writing);
		if (va->vars->stop == 1)
		{
			pthread_mutex_unlock(va->vars->writing);
			return (NULL);
		}
		pthread_mutex_unlock(va->vars->writing);
		
		pthread_mutex_lock(&va->vars->fork[va->r]);
		printing("has taken a fork\n", va);
		pthread_mutex_lock(&va->vars->fork[va->l]);
		printing("has taken a fork\n", va);
		
		pthread_mutex_lock(&va->vars->check);
		va->time_last_meal = timing(va);
		pthread_mutex_unlock(&va->vars->check);
	
		printing("is eating\n", va);
		my_sleep(va->vars->time_to_eat);
		pthread_mutex_unlock(&va->vars->fork[va->r]);
		pthread_mutex_unlock(&va->vars->fork[va->l]);
		printing("is sleeping\n", va);
		my_sleep(va->vars->time_to_slp);
		printing("is thinking\n", va);
		
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
			if (phil->vars->nbr_to_eat != -1)
			{
				// printf("all ate = %d\n",phil->vars->all_ate);
				if (phil->vars->all_ate == phil->vars->nbr_philo)
				{
					pthread_mutex_unlock(&phil->vars->check);
					return ;
				}
			}
			if (((int)(timing() - phil[i].time_last_meal) > phil->vars->time_to_die) && phil[i].ate != phil->vars->nbr_to_eat)
			{
				printing("died\n", phil);
				pthread_mutex_lock(phil->vars->writing);
				phil->vars->stop = 1;
				pthread_mutex_unlock(phil->vars->writing);
				pthread_mutex_unlock(&phil->vars->check);
				return ;
			}
			pthread_mutex_unlock(&phil->vars->check);
			usleep(100);
		}
	}
	return ;
}

void	start(t_list *va)
{
	int	i;

	i = 0;
	while (i < va->nbr_philo)
	{
		va->phil[i].time_last_meal = timing();
		// printf("id = %d\n",va->phil[i].id_philo);
		if (pthread_create(&va->phil[i].thread, NULL,\
			 philosofeur, &va->phil[i]))
			exit_free_msg(va, "Error\nin create thread\n", 2);
		usleep(100);
		i++;
	}
	i = 0;
	ihdiyay(va->phil);
	exit_free_msg(va, NULL, 0);
	// i = 0;
	// while (i < va->nbr_philo)
	// 	if (pthread_join(va->phil[i++].thread, NULL))
	// 		exit_free_msg(va, "Error\nin join\n", 2);
}

int	main(int ac, char **av)
{
	t_list	va;

	if (ac == 5 || ac == 6)
	{
		check_errors(av);
		fill_struct(av, &va);
		allocation(&va);
		initialisation(&va);
		start(&va);
	}
	else
		printf("wrong args\n");
	return (0);
}
