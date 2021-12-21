/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_ts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:10:52 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/21 15:45:52 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "is sleeping", \
		*philo->dead);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->par->time_sleep);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "is thinking", \
		*philo->dead);
	pthread_mutex_unlock(philo->print);
}

int	ft_eat(t_philo *philo)
{
	philo->time.reftime = get_time();
	pthread_mutex_lock(&philo->left);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "has taken a fork", \
		*philo->dead);
	pthread_mutex_unlock(philo->print);
	if (&philo->left == philo->right)
	{
		*philo->dead = 1;
		return (0);
	}
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "has taken a fork", \
		*philo->dead);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "is eating", \
		*philo->dead);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->par->time_eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(&philo->left);
	philo->last_eat = get_time();
	pthread_mutex_lock(philo->eat_times);
	philo->eat_index++;
	pthread_mutex_unlock(philo->eat_times);
	return (0);
}

void	*start_routine(void *par)
{
	t_philo			*philo;
	sig_atomic_t	ded;

	philo = (t_philo *)par;
	philo->eat_index = 0;
	philo->stop = 0;
	ded = 0;
	if (philo->id % 2)
		ft_usleep(philo->par->time_eat / 2);
	while (ded == 0)
	{
		if (philo->par->n_times_eat == -1 || \
			philo->eat_index <= philo->par->n_times_eat)
		{
			if (ft_eat(philo) || philo->stop == 1)
				return (NULL);
			ft_sleep(philo);
		}
		pthread_mutex_lock(philo->death);
		ded = *philo->dead;
		pthread_mutex_unlock(philo->death);
	}
	return (NULL);
}

void	*supervisor(void *par)
{
	t_all	*all;
	int		i;
	int		count;

	all = (t_all *)par;
	count = 0;
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
		{
			pthread_mutex_lock(&all->death);
			pthread_mutex_lock(&all->print);
			all->dead = 1;
			print_status(get_tstamp(all->p[i].time.start), i, "is dead", 0);
			pthread_mutex_unlock(&all->death);
			pthread_mutex_unlock(&all->print);
			return (NULL);
		}
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
