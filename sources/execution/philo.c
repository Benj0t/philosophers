#include "philo.h"

int		free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	return (1);
}

void	init_arr(int *arr, int len)
{
	int i;

	i = 0;
	while (i < len)
		arr[i++] = 0;
	arr[i] = -1;
}

int		init_data(t_params *par, t_data *data)
{
	int n_forks;

	n_forks = par->n_philos - 1;
	if (par->n_philos <= 2)
		n_forks = 2;
	data->philo = (pthread_t *)malloc(sizeof(pthread_t) * (par->n_philos));
	if (!data->philo)
		return (1);
	data->forks = (int *)malloc(sizeof(int) * (n_forks + 1));
	if (!data->forks)
		return (1);
	init_arr(data->forks, n_forks);
	return (0);
}

int		philosophers(t_params *par, t_data *data)
{
	if (init_data(par, data))
		return (free_data(data));
	create_threads(data, par->n_philos, par);
	return (0);
}