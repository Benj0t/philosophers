#include "philo.h"

int     verify_args(int argc, char **argv)
{
    if (ft_atoui(argv[1]) > 2147483647)
        return (1);
    if (ft_atoui(argv[2]) > 2147483647)
        return (1);
    if (ft_atoui(argv[3]) > 2147483647)
        return (1);
    if (ft_atoui(argv[4]) > 2147483647)
        return (1);
    if (argc == 6)
        if (ft_atoui(argv[5]) > 2147483647)
            return (1);
    return (0);
}

int     parser(int argc, char **argv, t_params *par)
{
    int i;

    i = 0;
    while (++i < argc)
    {
        if (is_digit(argv[i]))
            return (1);
    }
    par->n_times_eat = -1;
    if (verify_args(argc, argv))
        return (1);
    par->n_philos = ft_atoi(argv[1]);
    par->time_die = ft_atoi(argv[2]);
    par->time_eat = ft_atoi(argv[3]);
    par->time_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        par->n_times_eat = ft_atoi(argv[5]);
    if (!par->n_philos || !par->n_times_eat || !par->time_die || !par->time_eat || !par->time_sleep)
        return (1);
    return (0);
}