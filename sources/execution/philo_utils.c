/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:11:23 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/21 16:19:55 by bemoreau         ###   ########.fr       */
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

void	ft_eat2(t_philo *philo)
{
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
	ft_eat2(philo);
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
