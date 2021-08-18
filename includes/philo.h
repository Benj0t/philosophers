#ifndef _PHILO_H_
# define _PHILO_H_
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef struct	s_data
{
	int			*forks;
	int			*philo;
}				t_data;

typedef	struct	s_params
{
	int			n_philos;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			n_times_eat;
}				t_params;

int 	        ft_atoi(const char *str);
unsigned int	ft_atoui(const char *str);
int             is_digit(char *str);
void			init_arr(int *arr, int len);
int             parser(int argc, char **argv, t_params *par);
int				philosophers(t_params *par, t_data *data);
int			    create_threads(int *arr);
int             error_message(char *str);

#endif