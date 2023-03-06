/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:19:07 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/03/06 08:57:36 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <limits.h>
#include<stdlib.h>


typedef struct s_list{
	pthread_mutex_t	chopstick[200];
	pthread_t		philo[200];
	int				time_to_die;
	int				time_to_slp;
	int				time_to_eat;
	int				nbr_to_eat;
	int				nbr_philo;
	int				id_philo;
	int				index;
	int				time_at_start;
	int				x;
}t_list;

// typedef struct s_vars{
// 	t_list va;
// 	t_list *start;
// 	t_list *end;
// }t_vars;

long long	timing(t_list *va);
void	fill_struct(char **av, t_list *va);
void	check_errors(char **av);

// utils
int		ft_isdigit(char *str);
long	ft_atoi(const char *str);

#endif