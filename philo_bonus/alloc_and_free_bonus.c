/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_and_free_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:03:14 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/06/12 09:38:19 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	unlink_sem(void)
{
	sem_unlink("/ate");
	sem_unlink("/fork");
	sem_unlink("/check");
	sem_unlink("/writing");
	sem_unlink("/check_death");
}

static void	alloc_ph_fork(t_list *va)
{
	va->pid = malloc(sizeof(int) * va->nbr_philo);
	if (!va->pid)
	{
		free_all(va, 1);
		exit (1);
	}
	va->phil = malloc(sizeof(t_philo) * va->nbr_philo);
	if (!va->phil)
	{
		free(va->phil);
		free_all(va, 1);
		exit (1);
	}
}

int	for_norm(t_list *va)
{
	va->writing = sem_open("/writing", O_CREAT, 0644, 1);
	if (va->writing == SEM_FAILED)
	{
		sem_close(va->check_death);
		sem_close(va->fork);
		sem_close(va->check);
		sem_unlink("/check_death");
		return (sem_unlink("/check"), sem_unlink("/fork"), 1);
	}
	va->ate = sem_open("/ate", O_CREAT, 0644, 0);
	if (va->ate == SEM_FAILED)
	{
		sem_close(va->check_death);
		sem_close(va->fork);
		sem_close(va->check);
		sem_close(va->writing);
		sem_unlink("/check_death");
		sem_unlink("/fork");
		sem_unlink("/check");
		sem_unlink("/writing");
		return (1);
	}
	return (0);
}

int	allocation(t_list *va)
{
	unlink_sem();
	va->check_death = sem_open("/check_death", O_CREAT, 0600, 1);
	if (va->check_death == SEM_FAILED)
		return (1);
	va->fork = sem_open("/fork", O_CREAT, 0644, va->nbr_philo);
	if (va->fork == SEM_FAILED)
		return (sem_close(va->check_death), sem_unlink("/check_death"), 1);
	va->check = sem_open("/check", O_CREAT, 0644, 1);
	if (va->check == SEM_FAILED)
	{
		sem_close(va->check_death);
		sem_close(va->fork);
		return (sem_unlink("/check_death"), sem_unlink("/fork"), 1);
	}
	if (for_norm(va))
		return (1);
	alloc_ph_fork(va);
	return (0);
}

void	free_all(t_list *va, int nb)
{
	if (!nb)
	{
		free(va->phil);
		free(va->pid);
	}
	sem_close(va->ate);
	sem_close(va->fork);
	sem_close(va->writing);
	sem_close(va->check);
	sem_close(va->check_death);
	sem_unlink("/ate");
	sem_unlink("/fork");
	sem_unlink("/writing");
	sem_unlink("/check");
	sem_unlink("/check_death");
}
