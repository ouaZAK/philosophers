/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_and_free_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:03:14 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/09 16:07:54 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	allocation(t_list *va)
{
	sem_unlink("/fork");
	sem_unlink("/check");
	sem_unlink("/writing");
	sem_unlink("/check_death");
	va->pid = malloc(sizeof(int) * va->nbr_philo);
	if (!va->pid)
		return (1);
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

int	initialisation(t_list *va)
{
	int	i;

	i = -1;
	va->status = 5;
	while (++i < va->nbr_philo)
	{
		va->phil[i].id_philo = i;
		va->phil[i].stop = 0;
		va->phil[i].ate = 0;
		va->phil[i].vars = va;
	}
	return (0);
}

void	free_all(t_list *va)
{
	free(va->phil);
	free(va->pid);
	sem_close(va->fork);
	sem_close(va->writing);
	sem_close(va->check);
	sem_close(va->check_death);
	sem_unlink("/fork");
	sem_unlink("/writing");
	sem_unlink("/check");
	sem_unlink("/check_death");
}