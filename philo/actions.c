/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:54:58 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/14 13:28:14 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_philo *phil)
{
	pthread_mutex_lock(&phil->vars->fork[phil->r]);
	printing("has taken a fork\n", phil);
	pthread_mutex_lock(&phil->vars->fork[phil->l]);
	printing("has taken a fork\n", phil);
}

void	eating(t_philo *phil)
{
	printing("is eating\n", phil);
	my_sleep(phil->vars->time_to_eat, phil);
	pthread_mutex_unlock(&phil->vars->fork[phil->r]);
	pthread_mutex_unlock(&phil->vars->fork[phil->l]);
}

void	sleeping(t_philo *phil)
{
	printing("is sleeping\n", phil);
	my_sleep(phil->vars->time_to_slp, phil);
}

void	died(t_list *va, int i)
{
	pthread_mutex_lock(&va->check_dead);
	va->stop = 1;
	pthread_mutex_unlock(&va->check_dead);
	pthread_mutex_lock(&va->writing);
	printf("%ld %d died\n", timing() - va->time_at_start, \
	va->phil[i].id_philo + 1);
	pthread_mutex_unlock(&va->writing);
	pthread_mutex_unlock(&va->check);
}
