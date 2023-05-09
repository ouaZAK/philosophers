/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:22:22 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/09 09:22:36 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_for_childs(t_list *va, int i)
{
	while (i--)
	{
		va->pid_skip = waitpid(-1, &va->exit_status, 0);
		va->status = (va->exit_status >> 8) & 0x000000ff;
		if (va->status != 5)
			break ;
	}
	if (va->status != 5)
	{
		while (va->nbr_philo--)
		{
			if (va->pid[va->nbr_philo] != va->pid_skip)
				kill(va->pid[va->nbr_philo], SIGKILL);
		}
	}
}
