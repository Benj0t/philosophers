#ifndef _PHILO_H_
# define _PHILO_H_
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define MUTEX pthread_mutex_t
# define THREAD pthread_t
# define TRUE 0
# define FALSE 1

// REFACTO : Malloc une struct par philo dans all et mettre les single data a part !

typedef struct	s_data
{
	int				dead;
	MUTEX			*forks;
	MUTEX			print;
	MUTEX			death;
	THREAD			*philo;
}					t_data;

typedef struct	s_philo
{
	int				id;
	int				end_eat;
	THREAD			keeper;
}				t_philo;

typedef struct	s_time
{
	long int		start;
	long int		reftime;
	long int		curtime;
}				t_time;

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
	t_philo		*philo;
	t_data		*data;
	t_params	*par;
	t_time		*time;
}				t_all;

typedef struct	s_keep
{
	int			id;
	int			*dead;
	int			*end_eat;
	MUTEX		death;
	t_params	*par;
}				t_keep;

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
int			    create_threads(t_data *data, int nb, t_params *par, t_philo *philo);
int             error_message(char *str);

#endif