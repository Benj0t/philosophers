#include "philo.h"
//eating -> sleeping -> thinking -> beg
void	*start_routine(void *par)
{
	t_all			*all;
	int			 	num;
	int			 	i;

	gettimeofday(&(par->data->reftime), NULL);
	all = (t_all *)par;
	(void)par;
	i = 0;
	num = 0;
	/*while (num != 2)
	{
		if (!pthread_mutex_lock(all->data->forks[i])
		{
			num++;
			write(1, "got fork\n", 9);
		}
		i++;
		if (i == all->data->n_forks)
			i = 0;
	}
	*/
	return (NULL);
}

int	 create_threads(t_data *data, int nb, t_params *par)
{
	int i;
	t_all all;

	i = -1;
	all.data = data;
	all.par = par;
	while (++i < nb)
		if (pthread_create(&(data->philo)[i], NULL, &start_routine, &all))
			return (error_message("Cant create enough threads\n"));
	i = -1;
	while (++i < nb)
	{
		pthread_join(data->philo[i], NULL);
	}
	write(1, "boubou\n", 7);	
	return (0);
}