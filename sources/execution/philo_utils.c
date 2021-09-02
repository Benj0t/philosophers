#include "philo.h"

long int    get_time()
{
    long int            time;
    struct timeval      value;

    gettimeofday(&value, NULL);
    time = (value.tv_sec * 1000) + (value.tv_usec / 1000);
    return (time);
}