#include "../inc/philosophers.h"

void    *check_starvation_and_enough(void *philosophers)
{
    t_philos    *philos;
    long        current_time;
    int         i;

    philos = (t_philos *)philosophers;
    i = 0;
    while (philos[i].stop == 0)
    {
        i = 0;
        while (i < philos[0].nbr_philos)
        {
            current_time = get_time();
            if (current_time - philos[i].time_of_last_meal > philos[i].limit_of_life)
            {
                dead_philosopher(philos, i);
                return (NULL);
            }
            i++;
        }
        if (enough_meals(philos) || philos->stop)
            return (NULL);
    }
    return (NULL);
}

void    dead_philosopher(t_philos *philos, int i)
{
    philos->args->dead = 1; //Works for all philos?? Don't need philo[i].args->dead??
    pthread_mutex_lock(&philos->print_mutex); //No need for index?
    printf("%ld %d died\n", get_time() - philos[i].start_time, philos[i].id + 1); // philos->start_time ???
    i = 0;
    while (i < philos->nbr_philos)
    {
        philos[i].stop = 1;
        i++;
    }
    pthread_mutex_unlock(&philos->print_mutex); //No need for index?
}

void    *do_actions(void* philosopher)
{
    t_philos *philos;

    philos = (t_philos *)philosopher;
    philos->time_of_last_meal = get_time();
    philos->start_time = get_time();
    while (!philos->args->dead)
    {
        if (philos->args->dead || philos->stop || enough_meals(philos))
            return (NULL);
        ft_get_forks(philos);
        if (philos->args->dead || philos->stop || enough_meals(philos))
            return (NULL);
        ft_eat(philos);
        if (philos->args->dead || philos->stop || enough_meals(philos))
            return (NULL);
        ft_sleep(philos);
        if (philos->args->dead || philos->stop || enough_meals(philos))
            return (NULL);
        ft_think(philos);
        if (philos->args->dead || philos->stop || enough_meals(philos))  //REMOVE??
            return (NULL);  
    }
    return (NULL);
}

int enough_meals(t_philos *philos)
{
    int i;
    int enough;

    if (philos->nbr_meals_total < 1 || philos->nbr_meals_eaten == -1) // || philos->nbr_meals_eaten == -1)?????
        return (0);
    i = 0;
    enough = 1;
    while (i < philos[0].nbr_philos)
    {
        if (philos[i].nbr_meals_eaten < philos->nbr_meals_total)
            enough = 0;
        i++;
    }
    if (enough == 1)
    {
        i = 0;
        while (i < philos[0].nbr_philos)
        {
            philos[i].stop = 1;   // Explain why stop = 1 is necessary
            i++;
        }
        return (1);
    }
    return (0);
}