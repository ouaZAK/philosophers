#include "philo.h"

void	allocation(t_list *va)
{
	va->writing = malloc(sizeof(pthread_mutex_t));
	if (!va->writing)
		exit(2) ;
	va->fork = malloc(sizeof(pthread_mutex_t) * va->nbr_philo);
	if (!va->fork)
	{
		free(va->writing);
		exit(2) ;
	}
	va->phil = malloc(sizeof(t_philo) * va->nbr_philo);
	if (!va->phil)
	{
		free(va->writing);
		free(va->fork);
		exit (2) ;
	}
}

void	destroy_detach(t_list *va, int which)
{
	int	i;

	i = -1;
	if (which == 2)
	{
		while (++i < va->nbr_philo)
			pthread_mutex_destroy(&va->fork[i]);
		pthread_mutex_destroy(va->writing);
	}
	else
	{
		while (++i < va->nbr_philo)
		{
			pthread_mutex_destroy(&va->fork[i]);
			pthread_detach(va->phil[i].thread);
		}
		pthread_mutex_destroy(va->writing);
	}
}

void	exit_free_msg(t_list *va, char *str, int which)
{
	if (str)
		printf("%s",str);
	if (which == 1)
		pthread_mutex_destroy(va->writing);
	else if (which == 2)
		destroy_detach(va, which);
	else if (which == 0)
		destroy_detach(va, which);
	free(va->writing);
	free(va->phil);
	free(va->fork);
	exit(which);
}