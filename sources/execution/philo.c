#include "philo.h"

void	init_mutex(t_all *all)
{
	pthread_mutex_init(&all->print, NULL);
	pthread_mutex_init(&all->eat_times, NULL);
	pthread_mutex_init(&all->last_eat, NULL);
	pthread_mutex_init(&all->death, NULL);
}

void	assign_data(t_all *all, int i)
{
	all->p[i].id = i;
	all->p[i].par = &all->par;
	all->p[i].death = &(all->death);
	all->p[i].print = &(all->print);
	all->p[i].death = &(all->death);
	all->p[i].eat_times = &(all->eat_times);
}

int		init_data(t_all *all, t_params *par, t_philo **p)
{
	int i;

	i = 0;
	//ADD FREE_PARAMS BEFORE RET;
	*p = (t_philo *)malloc(sizeof(t_philo) * (par->n_philos));
	if (!p)
		return (1); // FREE DES TRUCS
	while (i < par->n_philos)
	{
		assign_data(all, i);
		pthread_mutex_init(p[i]->left, NULL); // Simplifier arg ?
		if (i == par->n_philos - 1)
			p[i]->right = p[0]->left;
		else
			p[i]->right = p[i + 1]->left;
		i++;
	}
	return (0);
}

int		philosophers(t_params *par)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	all->dead = 0;
	all->par = *par;
	init_mutex(all);
	if (!all)
		return (1);
	if (init_data(all, par, &all->p))
		return (1); // FREE DES TRUCS
	create_threads(par->n_philos, all);
	return (0);
}