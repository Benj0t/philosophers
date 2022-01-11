/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:10:38 by bemoreau          #+#    #+#             */
/*   Updated: 2022/01/08 10:25:04 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	all->p[i].eat_index = 0;
	all->p[i].stop = 0;
}

int	init_data(t_all *all, t_params *par)
{
	int	i;

	i = 0;
	all->p = (t_philo *)malloc(sizeof(t_philo) * (par->n_philos));
	if (!all->p)
		return (1);
	while (i < par->n_philos)
	{
		assign_data(all, i);
		pthread_mutex_init(&all->p[i].left, NULL);
		if (i == par->n_philos - 1)
			all->p[i].right = &all->p[0].left;
		else
			all->p[i].right = &all->p[i + 1].left;
		i++;
	}
	return (0);
}

void	end_simulation(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->par.n_philos)
	{
		pthread_join(all->p[i].thread, NULL);
	}
	pthread_join(all->supervisor, NULL);
	i = -1;
	while (++i < all->par.n_philos)
		pthread_mutex_destroy(&all->p[i].left);
	pthread_mutex_destroy(&all->print);
	pthread_mutex_destroy(&all->eat_times);
	pthread_mutex_destroy(&all->death);
}

int	philosophers(t_params *par)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	if (!all)
		return (1);
	all->p = NULL;
	all->dead = 0;
	all->n_eat_times = 0;
	all->par = *par;
	init_mutex(all);
	if (!all)
		return (ft_free(all));
	if (init_data(all, par))
		return (ft_free(all));
	create_threads(par->n_philos, all);
	ft_free(all);
	return (0);
}
