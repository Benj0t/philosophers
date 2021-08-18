#include "philo.h"

int     is_digit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] <= '9' && str[i] >= '0') && str[i] != '+')
            return (1); 
        i++;
    }
    return (0);
}