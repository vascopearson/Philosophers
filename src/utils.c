#include "../inc/philosophers.h"

int get_time()
{
    struct timeval current_time;
    long    time;

    gettimeofday(&current_time, NULL);
    time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
    printf("Time %li\n", time);
    return (time);
}

int ft_is_digit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < 48 || str[i] > 57)
            return (0);
        i++;
    }
    return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	sign = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (sign * num);
}

void	ft_usleep(int milisec) //CHECKKK
{
	long	time;

	time = get_time();
	usleep(milisec * 920);
	while (get_time() < time + milisec)
		usleep(milisec * 3);
}