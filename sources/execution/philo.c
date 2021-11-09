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

int		init_data(t_params *par, t_data *data, t_philo **philo)
{
	int i;

	i = 0;
	//ADD FREE_PARAMS BEFORE RET;
	*philo = (t_philo *)malloc(sizeof(t_philo) * (par->n_philos));
	if (!philo)
		return (1);
	data->philo = (THREAD *)malloc(sizeof(THREAD) * (par->n_philos));
	if (!data->philo)
		return (1);
	data->forks = (MUTEX *)malloc(sizeof(MUTEX) * (par->n_philos));
	if (!data->forks)
		return (1);
	init_mutex(data->forks, par->n_philos);
	pthread_mutex_init(&(data->print), NULL);
	return (0);
}

int		philosophers(t_params *par, t_data *data)
{
	t_philo	*philo;
	philo = NULL;
	if (init_data(par, data, &philo))
		return (free_data(data));
	create_threads(data, par->n_philos, par, philo);
	return (0);
}