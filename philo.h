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
# include <stdlib.h>

typedef struct philo{
	pthread_mutex_t	check;
	pthread_t		thread;
	int				id_philo;
	int 			r;
	int 			l;
	int				ate;
	int				stop;
	size_t			time_last_meal;
	struct s_list	*vars;
}t_philo;

typedef struct s_list{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*writing;
	int				time_to_die;
	int				time_to_slp;
	int				time_to_eat;
	int				nbr_to_eat;
	int				nbr_philo;
	size_t			time_at_start;
	t_philo			*phil;
}t_list;

// func
size_t		timing();
void		fill_struct(char **av, t_list *va);
void		check_errors(char **av);
void    	printing(char *str, t_philo *phil);
void		allocation(t_list *va);
void		initialisation(t_list *va);
void		exit_free_msg(t_list*va, char *str, int which);
void		my_sleep(int tts);

// utils
int		ft_isdigit(char *str);
long	ft_atoi(const char *str);

#endif