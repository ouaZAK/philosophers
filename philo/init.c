#include "philo.h"

void	initialisation(t_list *va)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(va->writing, NULL))
		exit_free_msg(va, "Error\nin mutex init\n", 0);
	va->stop = 0;
	va->all_ate = 0;
	pthread_mutex_init(&va->check, NULL);
	pthread_mutex_init(&va->check_dead, NULL);
	while (i < va->nbr_philo)
	{
		va->phil[i].id_philo = i;
		va->phil[i].ate = 0;
		va->phil[i].vars = va;
		va->phil[i].r = i;
		va->phil[i].l = (i + 1) % (va->nbr_philo);

		// printf("i = %d  l = %d\n",i,va->phil[i].l );
		if (pthread_mutex_init(&va->fork[i], NULL))
			exit_free_msg(va, "Error\nin mutex init\n", 1);
		i++;
	}
		va->time_at_start = timing();

}
