#include "philo.h"


int main()
{
	int i = -1;
	while (++i < 5)
    	printf("i left = %d  right = %d\n", i, (i + 1) % 5);

}
// while (1)
	// {
	// 	// printf("%lld %d is thinking\n", timing(va), va->id_philo);
	// 	pthread_mutex_lock(&va->vars->fork[va->id_philo - 1]);
	// 	pthread_mutex_lock(va->vars->writing);
	// 	printf("%lld %d has taken a fork left\n", timing(va) - va->vars->time_at_start, va->id_philo);
	// 	pthread_mutex_unlock(va->vars->writing);

	// 	pthread_mutex_lock(&va->vars->fork[((va->id_philo - 1) % va->vars->nbr_philo) + 1]);

	// 	pthread_mutex_lock(va->vars->writing);
	// 	printf("%lld %d has taken a fork rightt\n", timing(va) - va->vars->time_at_start, va->id_philo);
	// 	//time now - time at start > ttd
	// 	pthread_mutex_unlock(va->vars->writing);

	// 	pthread_mutex_lock(va->vars->writing);
	// 	printf("%lld %d is eating\n", timing(va) - va->vars->time_at_start, va->id_philo);
	// 	pthread_mutex_unlock(va->vars->writing);
	// 	usleep(va->vars->time_to_eat * 1000);

	// 	pthread_mutex_unlock(&va->vars->fork[va->id_philo - 1]);
	// 	pthread_mutex_lock(va->vars->writing);
	// 	printf("%lld %d has put a fork left\n", timing(va) - va->vars->time_at_start, va->id_philo);
	// 	pthread_mutex_unlock(va->vars->writing);
	// 	pthread_mutex_unlock(&va->vars->fork[((va->id_philo - 1) % va->vars->nbr_philo) + 1]);
	// 	pthread_mutex_lock(va->vars->writing);
	// 	printf("%lld %d has put a fork right\n", timing(va) - va->vars->time_at_start, va->id_philo);
	// 	pthread_mutex_unlock(va->vars->writing);


	// 	pthread_mutex_lock(va->vars->writing);
	// 	printf("%lld %d is sleeping\n", timing(va) - va->vars->time_at_start, va->id_philo);
	// 	pthread_mutex_unlock(va->vars->writing);
	// 	usleep(va->vars->time_to_slp * 1000);
		
	// 	pthread_mutex_lock(va->vars->writing);
	// 	printf("%lld %d is thinking\n", timing(va) - va->vars->time_at_start, va->id_philo);
	// 	pthread_mutex_unlock(va->vars->writing);
	// }

    
// size_t timing()
// {
//     struct timeval  curent;
//     gettimeofday(&curent, NULL);
//     return (curent.tv_sec * 1000) + (curent.tv_usec / 1000);
// }

// int main()
// {
//     size_t t_atstart;
//     size_t now;

//     t_atstart = timing();
//     usleep(100);
//     now = timing();
//     printf("%lld\n",t_atstart);
//     printf("%lld\n",now);
//     printf("%lld\n",now - t_atstart);
// }