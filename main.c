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
	// va->vars->time_at_start = timing(va); // time at start
	while (!va->stop && !va->died)
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
		printing("is eating\n", va);
		usleep(va->vars->time_to_eat * 1000);
		va->ate++;
		va->time_last_meal = timing(va);
		// if (va->vars->nbr_to_eat != -1)
		// 	if (va->ate == va->vars->nbr_philo)
		// 		va->stop = 1;

		pthread_mutex_unlock(&va->vars->fork[va->r]);
		pthread_mutex_unlock(&va->vars->fork[va->l]);

		printing("is sleeping\n", va);
		usleep(va->vars->time_to_slp * 1000);

		printing("is thinking\n", va);

	}
	return (NULL);
}

void	*ihdiyay(void *data)
{
	t_philo	*phil;
	// int		i;

	phil = (t_philo *)data;
	while (!phil->stop)
	{
		// i = -1;
		// while (++i < phil->vars->nbr_philo)
		// {
			pthread_mutex_lock(&phil->check);

			if (phil->vars->nbr_philo != -1)
				if (phil->ate == phil->vars->nbr_to_eat)
					phil->stop = 1;
			if ((timing() - phil->time_last_meal) > phil->vars->time_to_die && !phil->died)
			{
				// printf("last ===  %lld\n",(timing() - phil->time_last_meal));
				printing("died\n", phil);
				phil->died = 1;
				phil->stop = 1;
			}

			pthread_mutex_unlock(&phil->check);
		// }
	}
	return (NULL);
}

void	start(t_list *va)
{
	int	i;

	i = 0;
	va->time_at_start = timing();
	while (i < va->nbr_philo)
	{
		va->phil[i].time_last_meal = va->time_at_start;
		// printf("id = %d\n",va->phil[i].id_philo);
		if (pthread_create(&va->phil[i].thread, NULL,\
			 philosofeur, &va->phil[i]))
		{
			printf("Error\nin create thread\n");
			//free
			return ;
		}
		if (pthread_create(&va->fbi, NULL, ihdiyay, &va->phil[i]))
		{
			printf("Error\nin create thread\n");
			//free
			return ;
		}
		if (pthread_detach(va->fbi))
		{
			printf("Error\nin create thread\n");
			//free
			return ;
		}
		usleep(100);
		i++;
	}
	i = 0;
	while (i < va->nbr_philo)
	{
		if (pthread_join(va->phil[i++].thread, NULL))
		{
			printf("Error\nin join\n");
			//free
			return ;
		}
	}
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
