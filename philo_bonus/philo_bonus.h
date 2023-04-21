
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
#include <sys/stat.h>

typedef struct philo{
	pthread_t		thread;
	int				id_philo;
	int				ate;
	int				stop;
	struct s_list	*vars;
}t_philo;

typedef struct s_list{
	sem_t			*fork;
	sem_t			*writing;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_slp;
	int				nbr_to_eat;;
	int				nbr_philo;
	size_t			time_at_start;
	t_philo			*phil;
}t_list;

void	check_errors(char **av);
void	fill_struct(char **av, t_list *va);
void	initialisation(t_list *va);



#endif