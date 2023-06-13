/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:34:23 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/06/12 09:38:24 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
