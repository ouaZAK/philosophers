
#include "philo_bonus.h"

int main(int ac, char **av)
{
	t_list  va;

	if (ac == 5 || ac == 6)
	{
		check_errors(av);
		fill_struct(av, &va);
		allocation(&va);
		initialisation(&va);
		start(&va);
	}
	else
		printf("wrong args");
}