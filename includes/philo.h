#ifndef _PHILO_H_
# define _PHILO_H_
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define MUTEX pthread_mutex_t

typedef struct	s_data
{
	long int		start;
	long int		reftime;
	long int		curtime;
	int				n_forks;
	int				fid[2];
	int				dead;
	MUTEX			*forks;
	pthread_t		*philo;
}					t_data;

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
	int			id;
	t_data		*data;
	t_params	*par;
}				t_all;


void    		print_status(long int timestamp, int id, char *str);
void   		 	ft_putlnbr(long int nb);
void    		ft_putnbr(int nb);
void		    ft_putchar(char c);
long int    	get_time();
void  	    	ft_usleep(long int time);
long int	    get_tstamp(long int ref);
int 	        ft_atoi(const char *str);
unsigned int	ft_atoui(const char *str);
int             is_digit(char *str);
int             parser(int argc, char **argv, t_params *par);
int				philosophers(t_params *par, t_data *data);
int			    create_threads(t_data *data, int nb, t_params *par);
int             error_message(char *str);

#endif