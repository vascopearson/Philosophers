#include "../inc/philosophers.h"

void    init_philos(t_args *args)
{
    int         i;
    t_philos    *philos;

    philos = malloc(sizeof(t_philos) * args->nbr_philos);
    i = 0;
    while (i < args->nbr_philos)
    {
        philos[i].id = i;
        philos[i].nbr_philos = args->nbr_philos;
        philos[i].nbr_meals_eaten = 0;
        philos[i].nbr_meals_total = args->nbr_meals_for_each;
        philos[i].time_of_last_meal = get_time();
        philos[i].time_to_sleep = args->time_to_sleep;
        philos[i].time_to_eat = args->time_to_eat;
        philos[i].time_to_die = args->time_to_die;  // LIMIT OF LIFE ??
        philos[i].limit_of_life = args->time_to_die; //REMOVE??
        philos[i].dead = 0; // REMOVEEEE ??
        philos[i].stop = 0;
        philos[i].enough = 0; // REMOVEEE ???
        philos[i].args = args;
        philos[i].left_fork = &args->fork_mutexes[philos[i].id];
		philos[i].right_fork = &args->fork_mutexes[(philos[i].id + 1) % args->nbr_philos];
        i++;
    }
    args->philos = philos;
}

void    init_mutexes(t_args *args)
{
    pthread_mutex_t	*mutex;
    int philo_counter;

    philo_counter = args->nbr_philos;
    mutex = malloc(sizeof(pthread_mutex_t) * philo_counter);
    while (philo_counter--)
        pthread_mutex_init(&mutex[philo_counter], NULL);
    pthread_mutex_init(&args->print_mutex, NULL); //WHY IS THE PRINT_MUTEX IN ARGS AND NOT IN PHILOS
    args->fork_mutexes = mutex;
}


void    init_threads(t_args *args)
{
    pthread_t   *threads;
    pthread_t   starvation;
    int         philo_counter;

    philo_counter = args->nbr_philos;
    threads = malloc(sizeof(pthread_t) * philo_counter);
    while (philo_counter--)
        pthread_create(&threads[philo_counter], NULL, do_actions, (void *)&args->philos[philo_counter]);
    pthread_create(&starvation, NULL, check_starvation_and_enough, (void *)args->philos);
    pthread_join(starvation, NULL);
    args->philos_tid = threads;
    philo_counter = args->nbr_philos;
    if (philo_counter == 1)
		pthread_mutex_unlock(&args->fork_mutexes[0]);    // CHECKKKKK WHY THIS IS NECESSARY
    while (philo_counter--)
        pthread_join(args->philos_tid[philo_counter], NULL);
}
