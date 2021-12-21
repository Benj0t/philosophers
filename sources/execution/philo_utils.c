/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:11:23 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/21 12:56:46 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int    get_tstamp(unsigned int ref)
{
	struct timeval	  val;
	unsigned int			time;

	gettimeofday(&val, NULL);
	time = (val.tv_sec * 1000) + (val.tv_usec / 1000);
	return (time - ref);
}

long int	get_time()
{
	long int			time;
	struct timeval	  value;

	gettimeofday(&value, NULL);
	time = (value.tv_sec * 1000) + (value.tv_usec / 1000);
	return (time);
}

void		ft_usleep(long int time)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}

int		 check_stop(t_all *all)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < all->par.n_philos)
	{
		count += all->p[i++].stop;
	}
	return (count);
}