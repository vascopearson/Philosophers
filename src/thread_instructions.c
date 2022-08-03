#include "../inc/philosophers.h"

void    *check_starvation_and_enough(void *philosophers)
{
    t_philos    *philos;
    long        current_time;
    int         i;

    printf("5\n");
    philos = (t_philos *)philosophers;
    i = 0;
    while (philos[i].stop == 0)
    {
        printf("6\n");
        i = 0;
        printf("nbr_philos: %i\n", philos[i].args->nbr_philos);
        while (i < philos[i].args->nbr_philos)
        {
            printf("7\n");
            current_time = get_time();
            if (current_time - philos[i].time_of_last_meal > philos[i].args->time_to_die)
            {
                dead_philosopher(philos, i);
                return (NULL);
            }
            i++;
        }
    }
    enough_meals(philos);
    return (NULL);
}

void    dead_philosopher(t_philos *philos, int i)
{
    philos[i].dead = 1;
    pthread_mutex_lock(&philos[i].args->print_mutex);
    printf("%ld %d died\n", get_time() - philos[i].start_time, philos[i].id + 1);
    i = 0;
    while (i < philos[i].args->nbr_philos)
    {
        philos[i].stop = 1;
        i++;
    }
    pthread_mutex_unlock(&philos[i].args->print_mutex);
}

void    *do_actions(void* philosopher)
{
    t_philos *philos;

    philos = (t_philos *)philosopher;
    philos->time_of_last_meal = get_time();
    printf("1.5\n");
    philos->start_time = get_time();
    printf("2\n");
    while (!philos->dead)
    {
        printf("3\n");
        if (philos->dead || philos->stop || philos->enough)
            return (NULL);
        ft_get_forks(philos);
        if (philos->dead || philos->stop || philos->enough)
            return (NULL);
        ft_eat(philos);
        if (philos->dead || philos->stop || philos->enough)
            return (NULL);
        ft_sleep(philos);
        if (philos->dead || philos->stop || philos->enough)
            return (NULL);
        ft_think(philos);
    }
    return (NULL);
}

void enough_meals(t_philos *philos)
{
    int i;
    int enough;

    i = 0;
    enough = 1;
    while (i < philos[i].args->nbr_philos)
    {
        if (philos[i].nbr_meals_total == -1 || philos[i].nbr_meals_eaten <= 0)
            return ;
        if (philos[i].nbr_meals_eaten < philos->nbr_meals_total)
            enough = 0;
        i++;
    }
    if (enough == 1)
    {
        i = 0;
        while (i < philos[i].args->nbr_philos)
        {
            philos[i].enough = 1;
            i++;
        }
    }
}