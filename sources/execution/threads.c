#include "philo.h"
//eating -> sleeping -> thinking -> beg

void	philo_die(t_all *all, int id)
{
	(void)all;
	printf("Philosopher %d died\n", id);
	return;
}

void	eat(t_all *all, int id)
{
	int num;
	int fid[2];
	int i;

	i = 0;
	num = 0;
	all->data->reftime = get_time();
	while (num != 2)
	{
		if (!pthread_mutex_lock(&(all->data->forks[i])))
		{
			fid[num++] = i;
			printf("Philosopher %d has %d fork(s)\n", id, num);
		}
		all->data->curtime = get_time();
		//printf("%ld - %ld = %ld > %d\n", all->data->curtime, all->data->reftime, all->data->curtime - all->data->reftime, all->par->time_die);
		if ((all->data->curtime - all->data->reftime) > all->par->time_die)
		{
			printf("%ld - %ld = %ld > %d\n", all->data->curtime, all->data->reftime, all->data->curtime - all->data->reftime, all->par->time_die);
			philo_die(all, id);
			return;
		}
		i++;
		if (i == all->par->n_philos)
			i = 0;
	}
	if (num == 2)
	{
		printf("Philosopher %d starts eating\n", id);
		usleep(all->par->time_eat);
		all->data->curtime = get_time();
		if ((all->data->curtime - all->data->reftime) > all->par->time_die)
		{
			printf("%ld - %ld = %ld > %d\n", all->data->curtime, all->data->reftime, all->data->curtime - all->data->reftime, all->par->time_die);
			philo_die(all, id);
			return;
		}
		printf("Philosopher %d ends eating\n", id);
		pthread_mutex_unlock(&(all->data->forks[fid[0]]));
		pthread_mutex_unlock(&(all->data->forks[fid[1]]));
	}
}


void	*start_routine(void *par)
{
	t_all			*all;
	int				id;
	
	all = (t_all *)par;
	id = ++(all->id);
	while (1)
	{
		eat(all, id);
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
	return (0);
}