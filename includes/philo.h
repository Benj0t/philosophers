#ifndef _PHILO_H_
# define _PHILO_H_
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/time.h>

# define MUTEX pthread_mutex_t
# define THREAD pthread_t

// REFACTO : Malloc une struct par philo dans all et mettre les single data a part !

typedef struct		s_params
{
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_times_eat;
}					t_params;

typedef struct		s_time
{
	long int		start;
	long int		reftime;
	long int		curtime;
}					t_time;

typedef struct		s_philo
{
	THREAD			thread;
	int				id;
	t_time			time;
	MUTEX			left;
	MUTEX			right;
	MUTEX			*death;
	MUTEX			*print;
	int				eat_times;

	t_params		*par;
	int				*dead;
	int				eat_index;
	int				end_eat;
}					t_philo;

typedef	struct		s_all
{
	t_philo			*p;
	t_params		par;
	t_time			time;
	int				dead;

	MUTEX			print;
	MUTEX			death;
	// VV PIERROT VV
	MUTEX			last_eat;
	MUTEX			eat_times;
}					t_all;

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
int				philosophers(t_params *par);
int			    create_threads(int nb, t_all *all);
int             error_message(char *str);

#endif