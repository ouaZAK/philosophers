/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:54:58 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/06 12:20:17 by zouaraqa         ###   ########.fr       */
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
	my_sleep(phil->vars->time_to_eat);
	pthread_mutex_unlock(&phil->vars->fork[phil->r]);
	pthread_mutex_unlock(&phil->vars->fork[phil->l]);
}

void	sleeping(t_philo *phil)
{
	printing("is sleeping\n", phil);
	my_sleep(phil->vars->time_to_slp);
}

void	died(t_philo *phil)
{
	printing("died\n", phil);
	pthread_mutex_lock(&phil->vars->writing);
	phil->vars->stop = 1;
	pthread_mutex_unlock(&phil->vars->writing);
	pthread_mutex_unlock(&phil->vars->check);
}