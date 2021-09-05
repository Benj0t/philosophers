#include "philo.h"

void	philo_die(t_all *all, int id)
{
	pthread_mutex_lock(&(all->data->print));
	print_status(get_tstamp(all->time->start), id, "is dead\n");
	pthread_mutex_unlock(&(all->data->print));
	return;
}

int		check_death(t_all *all, int id)
{
	all->time->curtime = get_time();
	if ((all->time->curtime - all->time->reftime) > all->par->time_die)
	{
			philo_die(all, id);
			return (FALSE);
	}
	return (TRUE);
}

void	ft_sleep(t_all *all, int id)
{
	ft_usleep(all->par->time_sleep);
	pthread_mutex_lock(&(all->data->print));
	print_status(get_tstamp(all->time->start), id, "is sleeping\n");
	pthread_mutex_unlock(&(all->data->print));
}

void	*keeper_routine(void *par)
{
	long int	time;
	t_keep *keep;

	time = 0;
	keep = (t_keep *)par;
	while (!*(keep->end_eat) && time < keep->par->time_die)
	{
		time = get_time() - keep->ref;
		usleep(5);
	}
	if (time > keep->par->time_die)
	{
		pthread_mutex_lock(&(keep->death));
		print_status(get_tstamp(keep->start), keep->id, "is dead\n");
		*(keep->dead) = 1;
		pthread_mutex_unlock(&(keep->death));
	}
	return (NULL);
}

int		create_keeper(t_all *all, int id)
{
	t_keep	*keep;

	keep = malloc(sizeof(t_keep));
	if (!keep)
		return (1);
	keep->id = id;
	keep->end_eat = &(all->philo[id - 1].end_eat);
	keep->dead = &(all->data->dead);
	keep->death = all->data->death;
	keep->par = all->par;
	keep->start = all->time->start;
	keep->ref = all->time->reftime;
	if (pthread_create(&(all->philo[id - 1].keeper), NULL, &keeper_routine, keep))
		return (1);
	free(keep);
	return (0);
}

int		ft_eat(t_all *all, int id)
{
	all->time->reftime = get_time();
	all->philo[id - 1].end_eat = 0;
	if (create_keeper(all, id))
		return (error_message("Failed to create keeper\n"));
	pthread_mutex_lock(&(all->data->forks[id - 1]));
	pthread_mutex_lock(&(all->data->print));
	print_status(get_tstamp(all->time->start), id, "has taken a fork\n");
	pthread_mutex_unlock(&(all->data->print));
	pthread_mutex_lock(&(all->data->forks[id]));
	pthread_mutex_lock(&(all->data->print));
	print_status(get_tstamp(all->time->start), id, "has taken a fork\n");
	pthread_mutex_unlock(&(all->data->print));
	if (check_death(all, id))
		return (1);
	pthread_mutex_lock(&(all->data->print));
	print_status(get_tstamp(all->time->start), id, "is eating\n");
	pthread_mutex_unlock(&(all->data->print));
	ft_usleep(all->par->time_eat);
	all->philo[id - 1].end_eat = 1;
	if (check_death(all, id))
		return (1);
	pthread_mutex_unlock(&(all->data->forks[id -1]));
	pthread_mutex_unlock(&(all->data->forks[id]));
	return (0);
}

void	*start_routine(void *par)
{
	t_all			*all;
	int				id;

	all = (t_all *)par;
	id = ++(all->id);
	all->data->dead = 0;
	all->time->start = get_time();
	write(1, "euzp\n", 5);
	pthread_mutex_init(&(all->data->death), NULL);
	pthread_mutex_init(&(all->data->print), NULL);
	if (!(id % 2))
		ft_usleep(all->par->time_eat);
	while (1)
	{
		if (ft_eat(all, id))
			return (NULL);
		ft_sleep(all, id);
	}
	return (NULL);
}

int	 create_threads(t_data *data, int nb, t_params *par, t_philo *philo)
{
	int i;
	t_all all;

	i = -1;
	all.data = data;
	all.philo = philo;
	all.par = par;
	all.id = 0;
	all.time = malloc(sizeof(t_time));
	if (!all.time)
		return (error_message("Malloc crash\n"));
	write(1, "zuzp\n", 5);
	while (++i < nb)
		if (pthread_create(&(all.data->philo[i]), NULL, &start_routine, &all))
			return (error_message("Cant create enough threads\n"));
	i = -1;
	while (++i < nb)
		pthread_join(all.data->philo[i], NULL);
	return (TRUE);
}
