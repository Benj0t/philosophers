#include "philo.h"

void	init_mutex(t_all *all)
{
	pthread_mutex_init(&all->print, NULL);
	pthread_mutex_init(&all->eat_times, NULL);
	pthread_mutex_init(&all->death, NULL);
}

void	assign_data(t_all *all, int i)
{
	all->p[i].id = i;
	all->p[i].par = &all->par;
	all->p[i].death = &(all->death);
	all->p[i].print = &(all->print);
	all->p[i].dead = &(all->dead);
	all->p[i].n_eat_times = &(all->n_eat_times);
	all->p[i].eat_times = &(all->eat_times);
	all->p[i].eat_index = 0;
	all->p[i].last_eat = 0;
	all->p[i].right = NULL;
}

int		init_data(t_all *all, t_params *par)
{
	int i;

	i = 0;
	//ADD FREE_PARAMS BEFORE RET;
	all->p = (t_philo *)malloc(sizeof(t_philo) * (par->n_philos));
	if (!all->p)
		return (1); // FREE DES TRUCS
	while (i < par->n_philos)
	{
		assign_data(all, i);
		pthread_mutex_init(&all->p[i].left, NULL); // Simplifier arg ?
		if (i == par->n_philos - 1)
			all->p[i].right = &all->p[0].left;
		else
			all->p[i].right = &all->p[i + 1].left;
		i++;
	}
	return (0);
}

int		philosophers(t_params *par)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	all->dead = 0;
	all->n_eat_times = 0;
	all->par = *par;
	init_mutex(all);
	if (!all)
		return (1);
	if (init_data(all, par))
		return (1); // FREE DES TRUCS
	create_threads(par->n_philos, all);
	return (0);
}