/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:50:14 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/14 13:28:29 by zouaraqa         ###   ########.fr       */
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
	pthread_t		thread;
	int				id_philo;
	int				r;
	int				l;
	int				ate;
	size_t			time_last_meal;
	struct s_list	*vars;
}t_philo;

typedef struct s_list{
	pthread_mutex_t	*fork;
	pthread_mutex_t	writing;
	pthread_mutex_t	check;
	pthread_mutex_t	check_dead;
	int				stop;
	int				time_to_die;
	int				time_to_slp;
	int				time_to_eat;
	int				nbr_to_eat;
	int				nbr_philo;
	int				all_ate;
	size_t			time_at_start;
	t_philo			*phil;
}t_list;

// func
size_t		timing(void);
void		printing(char *str, t_philo *phil);
void		taking_forks(t_philo *phil);
void		eating(t_philo *phil);
void		sleeping(t_philo *phil);
void		my_sleep(int tts, t_philo *phil);
void		died(t_list *va, int i);
int			check_errors(char **av);
int			fill_struct(char **av, t_list *va);
int			allocation(t_list *va);
int			exit_free_msg(t_list*va, char *str, int which);
int			initialisation(t_list *va);
int			check_all_ate(t_list *va);

// utils
long		ft_atoi(const char *str);
int			ft_strlen(char *str);
int			ft_isdigit(char *str);

#endif