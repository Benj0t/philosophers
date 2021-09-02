#include "philo.h"
//eating -> sleeping -> thinking -> beg

void	philo_die(t_all *all, int id)
{
	print_status(get_tstamp(all->data->start), id, "has taken a fork\n");
	return;
}

void	eat(t_all *all, int id)
{
	int num;

	num = 0;
	all->data->reftime = get_time();
	while (num != 2)
	{
		if ((!pthread_mutex_lock(&(all->data->forks[id - 1]))))
		{
			num++;
			print_status(get_tstamp(all->data->start), id, "has taken a fork\n");
		}
		if (!pthread_mutex_lock(&(all->data->forks[id])))
		{
			num++;
			print_status(get_tstamp(all->data->start), id, "has taken a fork\n");
		}
		all->data->curtime = get_time();
		if ((all->data->curtime - all->data->reftime) > all->par->time_die)
		{
			philo_die(all, id);
			return;
		}
	}
	if (num == 2)
	{
		print_status(get_tstamp(all->data->start), id, "is eating\n");
		ft_usleep(all->par->time_eat);
		all->data->curtime = get_time();
		if ((all->data->curtime - all->data->reftime) > all->par->time_die)
		{
			printf("%ld - %ld = %ld > %d\n", all->data->curtime, all->data->reftime, all->data->curtime - all->data->reftime, all->par->time_die);
			philo_die(all, id);
			return;
		}
		pthread_mutex_unlock(&(all->data->forks[id -1]));
		pthread_mutex_unlock(&(all->data->forks[id]));
	}
}


void	*start_routine(void *par)
{
	t_all			*all;
	int				id;
	
	all = (t_all *)par;
	all->data->start = get_time();
	id = ++(all->id);
	if (!(id % 2))
		ft_usleep(all->par->time_eat);
	while (1)
		eat(all, id);
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
	return (0);
}