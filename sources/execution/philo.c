#include "philo.h"

int		free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	return (1);
}

void	init_mutex(MUTEX *arr, int len)
{
	int i;

	i = 0;
	while (i < len)
		pthread_mutex_init(&(arr[i++]), NULL);
}

int		init_data(t_params *par, t_data *data)
{

	data->n_forks = par->n_philos;
	data->philo = (pthread_t *)malloc(sizeof(pthread_t) * (par->n_philos));
	if (!data->philo)
		return (1);
	data->forks = (MUTEX *)malloc(sizeof(MUTEX) * (data->n_forks));
	if (!data->forks)
		return (1);
	init_mutex(data->forks, data->n_forks);
	return (0);
}

int		philosophers(t_params *par, t_data *data)
{
	if (init_data(par, data))
		return (free_data(data));
	create_threads(data, par->n_philos, par);
	return (0);
}