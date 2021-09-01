#ifndef _PHILO_H_
# define _PHILO_H_
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

# define MUTEX pthread_mutex_t

typedef struct	s_data
{
	int			n_forks;
	int			n_philos;
	MUTEX		*forks;
	pthread_t	*philo;
}				t_data;

typedef	struct	s_params
{
	int			n_philos;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			n_times_eat;
}				t_params;

typedef struct	s_all
{
	t_data		*data;
	t_params	*par;
}				t_all;

int 	        ft_atoi(const char *str);
unsigned int	ft_atoui(const char *str);
int             is_digit(char *str);
int             parser(int argc, char **argv, t_params *par);
int				philosophers(t_params *par, t_data *data);
int			    create_threads(t_data *data, int nb, t_params *par);
int             error_message(char *str);

#endif