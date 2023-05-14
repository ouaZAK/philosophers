/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:22:22 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/14 09:58:31 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_for_childs(t_list *va, int i)
{
	int	n;

	n = i;
	while (i--)
	{
		va->pid_skip = waitpid(-1, &va->exit_status, 0);
		va->status = (va->exit_status >> 8) & 0x000000ff;
		if (va->status != 5)
			break ;
	}
	if (va->status != 5)
	{
		while (n--)
		{
			if (va->pid[n] != va->pid_skip)
				kill(va->pid[n], SIGKILL);
		}
	}
}
