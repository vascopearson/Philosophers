#include "../inc/philosophers.h"

void    ft_get_forks(t_philos *philos)
{
	if (philos->id % 2 == 0 && philos->id + 1 != philos->nbr_philos)
	{
    	pthread_mutex_lock(philos->left_fork);
    	pthread_mutex_lock(philos->right_fork);
    	pthread_mutex_lock(&philos->print_mutex);
    	if (philos->stop != 1 && philos->dead != 1 && philos->enough != 1)
		{
			printf("%ld %d has taken a fork\n", \
				get_time() - philos->start_time, philos->id + 1);
			printf("%ld %d has taken a fork\n", \
				get_time() - philos->start_time, philos->id + 1);
		}
		pthread_mutex_unlock(&philos->print_mutex);
	}
	else //STILL PROBLEM, REMOVE?
	{
		pthread_mutex_lock(philos->left_fork);
    	pthread_mutex_lock(philos->right_fork);
    	pthread_mutex_lock(&philos->print_mutex);
    	if (philos->stop != 1 && philos->dead != 1 && philos->enough != 1)
		{
			printf("%ld %d has taken a fork\n", \
				get_time() - philos->start_time, philos->id + 1);
			printf("%ld %d has taken a fork\n", \
				get_time() - philos->start_time, philos->id + 1);
		}
		pthread_mutex_unlock(&philos->print_mutex);
	}
}

void    ft_eat(t_philos *philos)
{
    pthread_mutex_lock(&philos->print_mutex);
		printf("%ld %d is eating\n", \
			get_time() - philos->start_time, philos->id + 1);
	pthread_mutex_unlock(&philos->print_mutex);
    philos->nbr_meals_eaten += 1;
    philos->time_of_last_meal = get_time();
    ft_usleep(philos->time_to_eat);
    pthread_mutex_unlock(philos->left_fork);
    pthread_mutex_unlock(philos->right_fork);
}

void    ft_think(t_philos *philos)
{
    pthread_mutex_lock(&philos->print_mutex);
	printf("%ld %d is thinking\n", \
		get_time() - philos->start_time, philos->id + 1);
	pthread_mutex_unlock(&philos->print_mutex);
}

void    ft_sleep(t_philos *philos)
{
    pthread_mutex_lock(&philos->print_mutex);
	printf("%ld %d is sleeping\n", \
		get_time() - philos->start_time, philos->id + 1);
	pthread_mutex_unlock(&philos->print_mutex);
	ft_usleep(philos->time_to_sleep);
}