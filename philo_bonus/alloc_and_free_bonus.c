#include "philo_bonus.h"

void	allocation(t_list *va)
{
	va->fork = sem_open("fork", O_CREAT , 0644, va->nbr_philo);
	if (va->fork == SEM_FAILED)
		exit_free_msg(NULL, "Error\nin sem_open\n", 2);
	va->writing = sem_open("writing", O_CREAT, 0644, 1);
	if (va->writing == SEM_FAILED)
	{
		sem_close(va->fork);
		sem_unlink("fork");
		exit_free_msg(NULL, "Error\nin sem_open\n", 2);
	}
	va->phil = malloc(sizeof(t_philo) * va->nbr_philo);
	if (!va->phil)
	{
		sem_close(va->fork);
		sem_unlink("fork");
		sem_close(va->writing);
		sem_unlink("writing");
		exit_free_msg(NULL, "Error\nint malloc\n", 2);
	}
}

// void	destroy_detach(t_list *va, int which)
// {
// 	int	i;

// 	i = -1;
// 	if (which == 2)
// 	{
// 		while (++i < va->nbr_philo)
// 			pthread_mutex_destroy(&va->fork[i]);
// 		pthread_mutex_destroy(va->writing);
// 	}
// 	else
// 	{
// 		while (++i < va->nbr_philo)
// 		{
// 			pthread_mutex_destroy(&va->fork[i]);
// 			pthread_detach(va->phil[i].thread);
// 		}
// 		pthread_mutex_destroy(va->writing);
// 	}
// }

void	exit_free_msg(t_list *va, char *str, int which)
{
	if (str)
		printf("%s",str);
	// if (which == 1)
	// 	pthread_mutex_destroy(va->writing);
	// else if (which == 2)
	// 	destroy_detach(va, which);
	// else if (which == 0)
	// 	destroy_detach(va, which);
	free(va->writing);
	free(va->phil);
	free(va->fork);
	return (which);
}