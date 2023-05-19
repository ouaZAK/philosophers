/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:02:54 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/19 15:03:57 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <limits.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/stat.h>

typedef struct philo{
	pthread_t		thread;
	int				id_philo;
	int				ate;
	int				stop;
	size_t			last_meal;
	struct s_list	*vars;
}t_philo;

typedef struct s_list{
	sem_t			*fork;
	sem_t			*writing;
	sem_t			*check;
	sem_t			*check_death;
	pid_t			*pid;
	pid_t			pid_skip;
	int				status;
	int				exit_status;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_slp;
	int				nbr_to_eat;
	int				nbr_philo;
	int				all_ate;
	size_t			time_at_start;
	t_philo			*phil;
}t_list;

int		check_errors(char **av);
int		fill_struct(char **av, t_list *va);
int		initialisation(t_list *va);
int		exit_free_msg(t_list *va, char *str, int which);
int		allocation(t_list *va);
size_t	timing(void);
void	my_sleep(int tts);
void	printing(char *str, t_philo *phil);
void	wait_for_childs(t_list *va, int i);
void	free_all(t_list *va, int nb);

long	ft_atoi(const char *str);
int		ft_isdigit(char *str);
int		ft_strlen(char *str);

#endif