#include "philo.h"

long int    get_tstamp(unsigned int ref)
{
    struct timeval      val;
    unsigned int            time;

    gettimeofday(&val, NULL);
    time = (val.tv_sec * 1000) + (val.tv_usec / 1000);
    return (time - ref);
}

long int    get_time()
{
    long int            time;
    struct timeval      value;

    gettimeofday(&value, NULL);
    time = (value.tv_sec * 1000) + (value.tv_usec / 1000);
    return (time);
}

void        ft_usleep(long int time)
{
    long int    start;

    start = get_time();
    while ((get_time() - start) < time)
        usleep(time / 10);
}
