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
	t_philo	*va;

	va = (t_philo *)data;
	if ((va->id_philo + 1) % 2 == 0)
		usleep(100);
	va->vars->time_at_start = timing();
	// va->vars->time_at_start = timing(va); // time at start
	while (!va->stop && va->ate != va->vars->nbr_to_eat)
	{
		pthread_mutex_lock(&va->vars->fork[va->r]);
		printing("has taken a fork\n", va);
		pthread_mutex_lock(&va->vars->fork[va->l]);
		printing("has taken a fork\n", va);

		// if (va->vars->time_at_start - timing(va) > va->vars->time_to_die)
		// 	{
		// 		va->died = 1;
		// 		break;
		// 	}
		va->time_last_meal = timing(va);
		printing("is eating\n", va);
		// usleep(va->vars->time_to_eat * 1000);
		// my_sleep(timing(), va->vars->time_to_eat);
		// if (va->vars->nbr_to_eat != -1)
		// 	if (va->ate == va->vars->nbr_philo)
		// 		va->stop = 1;

		my_sleep(va->vars->time_to_eat);
		pthread_mutex_unlock(&va->vars->fork[va->r]);
		pthread_mutex_unlock(&va->vars->fork[va->l]);
		

		printing("is sleeping\n", va);
		my_sleep(va->vars->time_to_slp);
		// usleep(va->vars->time_to_slp * 1000);
		// my_sleep(timing(), va->vars->time_to_slp);

		printing("is thinking\n", va);
		va->ate++;

	}
	return (NULL);
}

int	ihdiyay(t_philo *phil)
{
	int	i;

	i = 0;
	while (!phil->stop)
	{
		i = -1;
		while (++i < phil->vars->nbr_philo)
		{
			// pthread_mutex_lock(&phil->check);
			if ((int)(timing() - phil->time_last_meal) > phil->vars->time_to_die && !phil->died)
			{
				// printf("did\n");
				printing("died\n", phil);
				phil->stop = 1;
				// printf("last ===  %lld\n",(timing() - phil->time_last_meal));
			// pthread_mutex_unlock(&phil->check);
			return (1);
			}
			if (phil->vars->nbr_to_eat != -1)
			{
				if (phil[i].ate == phil->vars->nbr_to_eat)
				{
					phil->stop = 1;
					return (1);
				}
			}
		}
	}
	return (0);
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
			exit_free("Error\nin create thread\n");

		// usleep(100);
		i++;
	}
	i = 0;
	if (ihdiyay(va->phil))
		exit(0);
	// while (i < va->nbr_philo)
	// {
	// 	if (pthread_create(&va->fbi, NULL, ihdiyay, &va->phil[i++]))
	// 		exit_free("Error\nin create thread\n");
	// 	if (pthread_detach(va->fbi))
	// 		exit_free("Error\nin detach thread\n");
	// }
	i = 0;
	while (i < va->nbr_philo)
		if (pthread_join(va->phil[i++].thread, NULL))
			exit_free("Error\nin join\n");
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
