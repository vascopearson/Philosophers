#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

struct	s_arg;

typedef struct s_philos
{
    int id;
    int nbr_philos;
    int nbr_meals_eaten;
    int nbr_meals_total;
    int time_to_sleep;
    int time_to_eat;
    int time_to_die;
    time_t time_of_last_meal;
    time_t start_time;
    int dead; // REMOVE ??
    int stop;
    int enough; // REMOVE ??
    struct s_args *args;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}   t_philos;

typedef struct s_args
{
    int nbr_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_meals_for_each;
    int dead;
    t_philos    *philos;
    pthread_t   *philos_tid;
    pthread_t   starvation; //REMOVE ??
    pthread_mutex_t   *fork_mutexes;
    pthread_mutex_t   print_mutex;
}   t_args;


int     check_invalid(int argc, char **argv);
void    wrong_args_message();
int     check_and_init_args(t_args *args, int argc, char **argv);

long    get_time();
int     ft_is_digit(char *str);
int	    ft_atoi(const char *str);
void	ft_usleep(int milisec);

void    init_philos(t_args *args);
void    init_mutexes(t_args *args);
void    init_threads(t_args *args);

void    *do_actions(void* philosopher);
void    *check_starvation_and_enough(void *philosophers);
void    dead_philosopher(t_philos *philos, int i);
int     enough_meals(t_philos *philos);

void    ft_get_forks(t_philos *philos);
void    ft_eat(t_philos *philos);
void    ft_think(t_philos *philos);
void    ft_sleep(t_philos *philos);

void    destroy_mutexes(t_args *args);
void    free_args(t_args *args);

#endif