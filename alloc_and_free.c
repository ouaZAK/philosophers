#include "philo.h"

void	allocation(t_list *va)
{
	va->writing = malloc(sizeof(pthread_mutex_t));
	if (!va->writing)
		return ;
	va->fork = malloc(sizeof(pthread_mutex_t) * va->nbr_philo);
	if (!va->fork)
	{
		free(va->writing);
		return ;
	}
	va->phil = malloc(sizeof(t_philo) * va->nbr_philo);
	if (!va->phil)
	{
		free(va->writing);
		free(va->fork);
		return ;
	}
}

void	exit_free(char *str)
{
	printf("%s",str);
	// free
	exit(2);
}