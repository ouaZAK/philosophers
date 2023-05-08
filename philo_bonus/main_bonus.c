/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:03:02 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/08 19:58:38 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*amksa(void *data)
{
	t_philo	*phil;

	phil = (t_philo *)data;
	while (1)
	{
		sem_wait(phil->vars->check);
		if (phil->vars->nbr_to_eat != -1)
		{
			sem_wait(phil->vars->check_death);
			if (phil->ate == phil->vars->nbr_to_eat)
			{
				sem_post(phil->vars->check_death);
				sem_post(phil->vars->check);
				exit (5);
			}
			sem_post(phil->vars->check_death);
		}
		if ((int)(timing() - phil->last_meal) > phil->vars->time_to_die)
		{
			sem_wait(phil->vars->writing);
			phil->stop = 1;
			sem_post(phil->vars->writing);
			sem_wait(phil->vars->writing);
			printf("%ld %d died\n", timing() - phil->vars->time_at_start, \
			phil->id_philo + 1);

			sem_post(phil->vars->check);
			exit (2);
		}
		sem_post(phil->vars->check);
	}
	return (NULL);
}

void	philosofeur(t_philo *phil)
{
	// sleep(1)
	// if (phil->id_philo % 2 == 0)
	// 	usleep(100);
	pthread_create(&phil->thread, NULL, amksa, phil);
	while (1)
	{
		printing("is thinking", phil);
		
		sem_wait(phil->vars->fork);
		printing("has taken a fork", phil);
		sem_wait(phil->vars->fork);
		printing("has taken a fork", phil);
		
		sem_wait(phil->vars->check);
		phil->last_meal = timing();
		sem_post(phil->vars->check);
		
		printing("is eating", phil);
		my_sleep(phil->vars->time_to_eat);
		sem_wait(phil->vars->check_death);
		phil->ate++;
		sem_post(phil->vars->check_death);
		
		sem_post(phil->vars->fork);
		sem_post(phil->vars->fork);
		
		printing("is sleeping", phil);
		my_sleep(phil->vars->time_to_slp);
		
		// printf("\n");
	}
	pthread_join(phil->thread, NULL);
	// exit (0); //darori i guess
}

int	start(t_list *va)
{
	int	i;

	i = 0;
	// printf("%d\n",va->nbr_philo);
	va->pid = malloc(sizeof(int) * 2);
	if (!va->pid)
		exit_free_msg(va, "Error\nmalloc\n", 2);
	va->time_at_start = timing();
	while (i < va->nbr_philo)
	{
		// if (!va->phil)
		// 	exit_free_msg(va, "Error\nmalloc\n", 2);
		va->phil->last_meal = timing();
		va->pid[i] = fork();
		if (va->pid[i] == 0)
			philosofeur(&va->phil[i]);
		// free(va->phil);
		i++;
	}
	while (i--)
	{
		waitpid(-1, &va->exit_status, 0);
		va->status = (va->exit_status >> 8) & 0x000000ff;
		if (va->status != 5)
			break ;
	}
	if (va->status != 5)
	{
		while (i--)
			kill(0, SIGKILL);	
	}
	return (0);
}

int main(int ac, char **av)
{
	t_list  va;

	if (ac != 5 && ac != 6)
		printf("wrong args");
	else
	{
		if (check_errors(av) || fill_struct(av, &va) \
			|| allocation(&va) || initialisation(&va) \
			|| start(&va))
			return (1);
	}
	return (0);
}