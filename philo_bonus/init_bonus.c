/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:03:07 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/08 18:52:40 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	initialisation(t_list *va)
{
	int	i;

	i = -1;
	while (++i < va->nbr_philo)
	{
		va->phil[i].id_philo = i;
		va->phil[i].stop = 0;
		va->status = 5;
		va->phil[i].vars = va;
	}
	return (0);
}