#include "philo.h"

void	philo_die(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "is dead\n");
	pthread_mutex_unlock(philo->print);
	return;
}

int		check_death(t_philo *philo)
{
	philo->time.curtime = get_time();
	if ((philo->time.curtime - philo->time.reftime) > philo->par->time_die)
	{
		philo_die(philo);
		return (1);
	}
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	ft_usleep(philo->par->time_sleep);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "is sleeping\n");
	pthread_mutex_unlock(philo->print);
}
// TEMPS DERNIER MANGER = ref pour le surveillant
int		ft_eat_left(t_philo *philo)
{
	philo->time.reftime = get_time();
	pthread_mutex_lock(&philo->left);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "has taken a fork\n");
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "has taken a fork\n");
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "is eating\n");
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->par->time_eat);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(philo->right);
	philo->last_eat = get_time();
	philo->eat_index++;
	return (0);
}

int		ft_eat_right(t_philo *philo)
{
	philo->time.reftime = get_time();
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "has taken a fork\n");
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(&philo->left);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "has taken a fork\n");
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time.start), philo->id, "is eating\n");
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->par->time_eat);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(philo->right);
	philo->last_eat = get_time();
	philo->eat_index++;
	return (0);
}

void	*start_routine(void *par)
{
	t_philo			*philo;
	sig_atomic_t	ded;

	philo = (t_philo *)par;
	philo->eat_times = 0;
	ded = 0;
	philo->dead = 0;
	pthread_mutex_lock(philo->print);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->print);
	pthread_mutex_unlock(philo->print);
	philo->time.start = get_time();
	philo->last_eat = philo->time.start;
	while (!ded)
	{
		if (philo->par->n_times_eat == -1 || philo->eat_index < philo->par->n_times_eat)
		{
			if (philo->id % 2)
			{
				if (ft_eat_right(philo))
					return (NULL);
			}
			else
				if (ft_eat_left(philo))
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
	t_all *all;
	int		i;

	all = (t_all *)par;
	i = 0;
	while (i < all->par.n_philos)
	{
		if (get_tstamp(all->p[i].last_eat) > all->par.time_die)
		{
			pthread_mutex_lock(&all->death);
			all->dead = 1;
			pthread_mutex_unlock(&all->death);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

int	 create_threads(int nb, t_all *all)
{
	int i;

	i = -1;
	while (++i < nb)
		if (pthread_create(&(all->p[i].thread), NULL, &start_routine, &(all->p[i])))
			return (error_message("Cant create enough threads\n"));
	i = -1;
	pthread_create(&(all->supervisor), NULL, &supervisor, &all);
	while (++i < nb)
		pthread_join(all->p[i].thread, NULL);
	pthread_join(all->supervisor, NULL);
	return (0);
}
