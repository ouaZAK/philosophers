/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:49:23 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/05 16:54:02 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialisation(t_list *va)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&va->writing, NULL)
		|| pthread_mutex_init(&va->check, NULL)
		|| pthread_mutex_init(&va->check_dead, NULL))
		if (exit_free_msg(va, "Error\nin mutex init\n", 0))
			return (1);
	va->stop = 0;
	va->all_ate = 0;
	while (i < va->nbr_philo)
	{
		va->phil[i].id_philo = i;
		va->phil[i].ate = 0;
		va->phil[i].vars = va;
		va->phil[i].r = i;
		va->phil[i].l = (i + 1) % (va->nbr_philo);
		if (pthread_mutex_init(&va->fork[i], NULL))
			if (exit_free_msg(va, "Error\nin mutex init\n", 1))
				return (1);
		i++;
	}
	va->time_at_start = timing();
	return (0);
}
