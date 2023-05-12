/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:50:21 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/12 11:18:30 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printing(char *str, t_philo *phil)
{
	sem_wait(phil->vars->writing);
	if (!phil->stop)
		printf("%ld %d %s\n", timing() - phil->vars->time_at_start, \
			phil->id_philo + 1, str);
	sem_post(phil->vars->writing);
}
