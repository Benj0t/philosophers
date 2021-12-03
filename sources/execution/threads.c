#include "philo.h"

void	philo_die(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time->start), id, "is dead\n");
	pthread_mutex_unlock(philo->print);
	return;
}

int		check_death(t_philo *philo)
{
	philo->time->curtime = get_time();
	if ((philo->time->curtime - philo->time->reftime) > philo->par->time_die)
	{
		philo_die(philo);
		return (FALSE);
	}
	return (TRUE);
}

void	ft_sleep(t_philo *philo)
{
	ft_usleep(philo->par->time_sleep);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time->start), id, "is sleeping\n");
	pthread_mutex_unlock(philo->print);
}
// TEMPS DERNIER MANGER
int		ft_eat(t_philo *philo)
{
	philo->time->reftime = get_time();
	philo->end_eat = 0;
	pthread_mutex_lock(&philo->left);
	pthread_mutex_lock(philo->data->print);
	print_status(get_tstamp(philo->time->start), id, "has taken a fork\n");
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(&philo->right);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time->start), id, "has taken a fork\n");
	pthread_mutex_unlock(philo->print);
	if (check_death(philo))
		return (1);
	pthread_mutex_lock(philo->print);
	print_status(get_tstamp(philo->time->start), id, "is eating\n");
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->par->time_eat);
	philo->end_eat = 1;
	if (check_death(philo))
		return (1);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(&philo->right);
	return (0);
}

void	*start_routine(void *par)
{
	t_philo			*philo;
	sig_atomic_t	ded;

	philo = (t_philo *)par;
	philo->time->start = get_time();
	philo->eat_times = 0;
	ded = false;
	philo->dead = 
	if (!(philo->id % 2)) // NON, C EST RAMADAN (FT_SWAP LES FOURHCETTES IF ID % 2)
		ft_usleep(philo->par->time_eat);
	while (!ded)
	{
		if (philo->eat_times < philo->par->n_times_eat)
		{
			if (ft_eat(philo))
				return (NULL);
			ft_sleep(philo);
		}
		pthread_mutex_unlock(philo->death);
		ded = philo->dead;
		pthread_mutex_unlock(philo->death);
	}
	return (NULL);
}

int	 create_threads(int nb, t_all *all)
{
	int i;

	i = -1;
	while (++i < nb)
		if (pthread_create(&(all->p[i]->thread), NULL, &start_routine, &(all->p[i]))
			return (error_message("Cant create enough threads\n"));
	i = -1;
	while (++i < nb)
		pthread_join(all->p[i], NULL);
	return (TRUE);
}
