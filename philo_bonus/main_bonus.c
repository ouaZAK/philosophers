
#include "philo_bonus.h"

void	philosofeur(t_philo *phil)
{
	// sleep(1)
	printf("ha = %d\n", phil->id_philo);
	exit(0);
}

void	start(t_list *va)
{
	int	i;

	i = 0;
	// printf("%d\n",va->nbr_philo);
	va->pid = malloc(sizeof(int) * va->nbr_philo);
	if (!va->pid)
		exit_free_msg(va, "Error\nmalloc\n", 2);
	while (i < va->nbr_philo)
	{
		if (!va->phil)
			exit_free_msg(va, "Error\nmalloc\n", 2);
		va->pid[i] = fork();
		if (va->pid[i] == 0)
			philosofeur(&va->phil[i]);
		// free(va->phil);
		i++;
	}
	while (i--)
		wait(NULL);

}

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