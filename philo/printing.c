
#include "philo.h"

void    printing(char *str, t_philo *phil)
{
    pthread_mutex_lock(phil->vars->writing);
    if (!phil->vars->stop)
        printf("%ld %d %s",timing() - phil->vars->time_at_start, \
            phil->id_philo + 1, str);
    pthread_mutex_unlock(phil->vars->writing);
}