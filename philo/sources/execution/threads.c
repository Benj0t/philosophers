/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:10:52 by bemoreau          #+#    #+#             */
/*   Updated: 2022/01/09 17:00:11 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat2_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->left);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "has taken a fork", \
		*philo->dead);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "is eating", \
		*philo->dead);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->eat_times);
	philo->last_eat = get_time();
	philo->eat_index++;
	pthread_mutex_unlock(philo->eat_times);
	ft_usleep(philo->par->time_eat);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(philo->right);
}

int	ft_eat_right(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "has taken a fork", \
		*philo->dead);
	pthread_mutex_unlock(philo->print);
	if (&philo->left == philo->right)
	{
		*philo->dead = 1;
		return (0);
	}
	ft_eat2_right(philo);
	return (0);
}

void	*announce_death(t_all *all, int id, int print)
{
	pthread_mutex_lock(&all->death);
	pthread_mutex_lock(&all->print);
	all->dead = 1;
	print_status(get_tstamp(all->p[id].time.start), id, "is dead", print);
	pthread_mutex_unlock(&all->death);
	pthread_mutex_unlock(&all->print);
	pthread_mutex_unlock(all->p[id].eat_times);
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
		if (check_stop(all) == all->par.n_philos)
			return (announce_death(all, i, 1));
		if (get_tstamp(all->p[i].last_eat) > all->par.time_die && \
													!all->p[i].stop)
			return (announce_death(all, i, 0));
		pthread_mutex_unlock(all->p[i].eat_times);
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
	pthread_create(&(all->supervisor), NULL, &supervisor, all);
	end_simulation(all);
	return (0);
}
