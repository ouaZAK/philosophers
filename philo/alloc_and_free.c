/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:49:32 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/06 12:20:05 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocation(t_list *va)
{
	va->fork = malloc(sizeof(pthread_mutex_t) * va->nbr_philo);
	if (!va->fork)
		return (1);
	va->phil = malloc(sizeof(t_philo) * va->nbr_philo);
	if (!va->phil)
	{
		free(va->fork);
		return (1);
	}
	return (0);
}

void	destroy_detach(t_list *va, int which)
{
	int	i;

	i = -1;
	if (which == 2)
	{
		while (++i < va->nbr_philo)
			pthread_mutex_destroy(&va->fork[i]);
		pthread_mutex_destroy(&va->writing);
	}
	else
	{
		while (++i < va->nbr_philo)
		{
			pthread_mutex_destroy(&va->fork[i]);
			pthread_detach(va->phil[i].thread);
		}
		pthread_mutex_destroy(&va->writing);
	}
	free(va->phil);
	free(va->fork);
}

int	exit_free_msg(t_list *va, char *str, int which)
{
	if (str)
		printf("%s", str);
	if (which == 1)
		pthread_mutex_destroy(&va->writing);
	else if (which == 2)
		destroy_detach(va, which);
	else if (which == 0)
		destroy_detach(va, which);
	free(va->phil);
	free(va->fork);
	return (1);
}
