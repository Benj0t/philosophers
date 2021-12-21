/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:10:52 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/21 16:19:08 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*announce_death(t_all *all, int id)
{
	pthread_mutex_lock(&all->death);
	pthread_mutex_lock(&all->print);
	all->dead = 1;
	print_status(get_tstamp(all->p[id].time.start), id, "is dead", 0);
	pthread_mutex_unlock(&all->death);
	pthread_mutex_unlock(&all->print);
	return (NULL);
}

void	*supervisor(void *par)
{
	t_all	*all;
	int		i;

	all = (t_all *)par;
	i = 0;
	while (i < all->par.n_philos)
	{
		pthread_mutex_lock(all->p[i].eat_times);
		if (all->p[i].eat_index == all->par.n_times_eat)
			all->p[i].stop = 1;
		pthread_mutex_unlock(all->p[i].eat_times);
		if (check_stop(all) == all->par.n_philos)
		{
			pthread_mutex_lock(&all->death);
			all->dead = 1;
			pthread_mutex_unlock(&all->death);
			return (NULL);
		}
		if (get_tstamp(all->p[i].last_eat) > all->par.time_die)
			return (announce_death(all, i));
		i++;
		if (i == all->par.n_philos)
			i = 0;
	}
	return (NULL);
}

int	create_threads(int nb, t_all *all)
{
	int		i;
	long	time;

	time = get_time();
	i = -1;
	while (++i < nb)
	{
		all->p[i].time.start = time;
		all->p[i].last_eat = all->p[i].time.start;
		if (pthread_create(&(all->p[i].thread), NULL, &start_routine, \
			&(all->p[i])))
			return (error_message("Cant create enough pthread_ts\n"));
	}
	i = -1;
	pthread_create(&(all->supervisor), NULL, &supervisor, all);
	while (++i < nb)
		pthread_join(all->p[i].thread, NULL);
	pthread_join(all->supervisor, NULL);
	return (0);
}
