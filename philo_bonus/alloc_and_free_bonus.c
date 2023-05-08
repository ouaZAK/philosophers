/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_and_free_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:03:14 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/08 19:09:51 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	allocation(t_list *va)
{
	sem_unlink("/fork");
	sem_unlink("/check");
	sem_unlink("/writing");
	sem_unlink("/check_death");
	va->check_death = sem_open("/check_death", O_CREAT, 0644, 1);
	if (va->check_death == SEM_FAILED)
		return (1);
	va->fork = sem_open("/fork", O_CREAT, 0644, va->nbr_philo);
	if (va->fork == SEM_FAILED)
		return (1);
	va->check = sem_open("/check", O_CREAT, 0644, 1);
	if (va->check == SEM_FAILED)
		return (1);
	va->writing = sem_open("/writing", O_CREAT, 0644, 1);
	if (va->writing == SEM_FAILED)
		return (1);
	va->phil = malloc(sizeof(t_philo) * va->nbr_philo);
	if (!va->phil)
		return (1);
	return (0);
}

// void	destroy_detach(t_list *va, int which)
// {
// 	int	i;

// 	i = -1;
// 	if (which == 2)
// 	{
// 		while (++i < va->nbr_philo)
// 			pthread_mutex_destroy(&va->fork[i]);
// 		pthread_mutex_destroy(va->writing);
// 	}
// 	else
// 	{
// 		while (++i < va->nbr_philo)
// 		{
// 			pthread_mutex_destroy(&va->fork[i]);
// 			pthread_detach(va->phil[i].thread);
// 		}
// 		pthread_mutex_destroy(va->writing);
// 	}
// }

int	exit_free_msg(t_list *va, char *str, int which)
{
	if (str)
		printf("%s",str);
	// if (which == 1)
	// 	pthread_mutex_destroy(va->writing);
	// else if (which == 2)
	// 	destroy_detach(va, which);
	// else if (which == 0)
	// 	destroy_detach(va, which);
	free(va->writing);
	free(va->phil);
	// free(va->fork);
	return (which);
}