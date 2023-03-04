/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:50:18 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/03/04 10:21:51 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long	timeing(char c)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

// void	*do_it(void *data)
// {
// 	// *(int *)data = 3;
// 	// int *x = malloc(sizeof(int));
// 	// *x =  5;
// 	// printf("%d\n",*(int *)data);
// 	int m = *(int *)data;
// 	int	*x = malloc(sizeof(int));
// 	*x = *(int *)data;
// 	printf("tab[i] = %d\n",m);
// 	return (x);
// }

void	*philosofeuur(void *data)
{
	t_list	*va;
	int		n;
n = -1;
	va = (t_list *)data;
	// printf("philo  ==> %d\n", va->nbr_to_eat);
	pthread_mutex_lock(&va->chopstick);
	while (++n < va->nbr_philo)
		va->nbr_to_eat++;
	// usleep(200);
	printf("i am philo nbr : %d\n", va->nbr_to_eat);
	pthread_mutex_unlock(&va->chopstick);
	// sleep(2);
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	t[200];
	t_list		*va;
	int			i;
	int			x;

	i = 0;
	va = malloc(sizeof(t_list));
	x = atoi(av[1]);
	printf("x = %d\n",x);
	va->nbr_philo = x;
	va->nbr_to_eat = 0;
	pthread_mutex_init(&va->chopstick, NULL);
	while (i < 3)
	{
		// va->nbr_philo = i;
		// printf("va->id = %d\n",va->nbr_philo);
		if (pthread_create(&t[i], NULL, &philosofeuur, va) != 0)
		{
			write(2, "Error\n",6);
			exit(1);
		}
		// usleep(1000);
		// printf("thread %d started\n",i);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		// printf("%d i\n",i);
		if (pthread_join(t[i], NULL) != 0)
		{
			write(2, "Error\n",6);
			exit(1);
		}
		// printf("thread %d finish\n",i);
		i++;
	}
	pthread_mutex_destroy(&va->chopstick);
	
}

// int main()
// {
// 	pthread_t	t[4];
// 	int			tab[4] = {1, 2, 3, 4};
// 	int			i;
// 	int			*x;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		x = malloc(sizeof(int));
// 		*x = tab[i];
// 	// printf("[%d]\n",*x);
// 		pthread_create(&t[i++], NULL, do_it, x);
// 	}
// 	i = 0;
// 	while (i < 4)
// 	{	pthread_join(t[i++], (void **)&x);
// 	printf("fron main = %d\n", *x);}
// }

// int main()
// {
// 	pthread_t	t1;
// 	int			*x;
// 	int	n;

// 	n = 9;
// 	pthread_create(&t1, NULL, do_it, &n);
// 	pthread_join(t1, (void **)&x);
// 	printf("n = %d\nx = %d\n",n,*x);
// 	// free(x);
// }