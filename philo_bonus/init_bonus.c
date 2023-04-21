#include "philo_bonus.h"

void	initialisation(t_list *va)
{
	int	i;

	i = -1;
	while (++i < va->nbr_philo)
	{
		va->phil = i;
	}
}