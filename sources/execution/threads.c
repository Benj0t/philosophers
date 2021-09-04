#include "philo.h"
//eating -> sleeping -> thinking -> beg

void	philo_die(t_all *all, int id)
{
	pthread_mutex_lock(&(all->data->print));
	print_status(get_tstamp(all->time->start), id, "has taken a fork\n");
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

void	ft_eat(t_all *all, int id)
{
	all->time->reftime = get_time();
	pthread_mutex_lock(&(all->data->forks[id - 1]));
	pthread_mutex_lock(&(all->data->print));
	print_status(get_tstamp(all->time->start), id, "has taken a fork\n");
	pthread_mutex_unlock(&(all->data->print));
	pthread_mutex_lock(&(all->data->forks[id]));
	pthread_mutex_lock(&(all->data->print));
	print_status(get_tstamp(all->time->start), id, "has taken a fork\n");
	pthread_mutex_unlock(&(all->data->print));
	if (check_death(all, id))
		return ;
	pthread_mutex_lock(&(all->data->print));
	print_status(get_tstamp(all->time->start), id, "is eating\n");
	pthread_mutex_unlock(&(all->data->print));
	ft_usleep(all->par->time_eat);
	if (check_death(all, id))
		return ;
	pthread_mutex_unlock(&(all->data->forks[id -1]));
	pthread_mutex_unlock(&(all->data->forks[id]));
}


void	*start_routine(void *par)
{
	t_all			*all;
	int				id;
	
	all = (t_all *)par;
	all->time->start = get_time();
	id = ++(all->id);
	if (!(id % 2))
		ft_usleep(all->par->time_eat);
	while (1)
	{
		ft_eat(all, id);
		ft_sleep(all, id);
	}
	return (NULL);
}

int	 create_threads(t_data *data, int nb, t_params *par)
{
	int i;
	t_all all;

	i = -1;
	all.data = data;
	all.par = par;
	all.id = 0;
	while (++i < nb)
	{
		if (pthread_create(&(data->philo)[i], NULL, &start_routine, &all))
			return (error_message("Cant create enough threads\n"));
	}
	i = -1;
	while (++i < nb)
	{
		pthread_join(data->philo[i], NULL);
	}
	write(1, "boubou\n", 7);
	return (TRUE);
}