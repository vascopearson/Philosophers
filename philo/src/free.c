#include "../inc/philosophers.h"

void    destroy_mutexes(t_args *args)
{
    int philo_counter;

    philo_counter = args->nbr_philos;
    while (philo_counter--)
    {
        pthread_mutex_unlock(&args->fork_mutexes[philo_counter]);
        pthread_mutex_destroy(&args->fork_mutexes[philo_counter]);
    }
    pthread_mutex_unlock(&args->print_mutex); //CHECKKKKK
    pthread_mutex_destroy(&args->print_mutex);
}

void    free_args(t_args *args)
{
	free(args->philos_tid);
	free(args->philos);
	free(args->fork_mutexes);
}