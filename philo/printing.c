/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:50:21 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/06/12 09:38:56 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing(char *str, t_philo *phil)
{
	pthread_mutex_lock(&phil->vars->check_dead);
	if (!phil->vars->stop)
		printf("%ld %d %s", timing() - phil->vars->time_at_start, \
			phil->id_philo + 1, str);
	pthread_mutex_unlock(&phil->vars->check_dead);
}
