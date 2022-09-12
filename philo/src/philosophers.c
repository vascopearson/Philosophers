#include "../inc/philosophers.h"

int main(int argc, char **argv)
{
    t_args  args;

    if (check_invalid(argc, argv))
        return (1);
    if (check_and_init_args(&args, argc, argv))
        return (1);
    init_mutexes(&args);
    init_philos(&args);
    init_threads(&args);
    destroy_mutexes(&args);
    free_args(&args);
    return (0);
}

int check_invalid(int argc, char **argv)
{
    int i;

    if (argc != 5 && argc != 6)
    {
        wrong_args_message();
        return (1);
    }
    i = 1;
    while (i < argc)
    {
        if (!ft_is_digit(argv[i]))
        {
            printf("One of the arguments is not a number!\n");
            return (1);
        }
        i++;
    }
    return (0);
}

void    wrong_args_message()
{
    printf("------------ Wrong arguments! -----------\n");
    printf("-----------------------------------------\n");
    printf("- Please enter the following arguments: -\n");
    printf("     Arg1: [Number of philosophers]      \n");
	printf("     Arg2: [Time to die]                 \n");
	printf("     Arg3: [Time to eat]                 \n");
	printf("     Arg4: [Time to sleep]               \n");
	printf("     Arg5 (optional): [Number of meals]  \n");
    printf("-----------------------------------------\n");
}

int check_and_init_args(t_args *args, int argc, char **argv)
{
    args->nbr_philos = ft_atoi(argv[1]);
    args->time_to_die = ft_atoi(argv[2]);
    args->time_to_eat = ft_atoi(argv[3]);
    args->time_to_sleep = ft_atoi(argv[4]);
    args->dead = 0;
    if (args->nbr_philos < 1)
        return (1);
    if (argc == 6)
    {
        args->nbr_meals_for_each = ft_atoi(argv[5]);
        if (args->nbr_meals_for_each < 1)
			return (1);
    }
    if (argc == 5)
        args->nbr_meals_for_each = -1;
    return (0);
}