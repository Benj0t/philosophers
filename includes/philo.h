/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:51:44 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/21 15:51:00 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/time.h>

typedef struct s_params
{
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_times_eat;
}					t_params;

typedef struct s_time
{
	long int		start;
	long int		reftime;
	long int		curtime;
}					t_time;

typedef struct s_philo
{
	t_params				*par;

	pthread_t				thread;
	int						id;
	t_time					time;
	pthread_mutex_t			left;
	pthread_mutex_t			*right;
	pthread_mutex_t			*death;
	pthread_mutex_t			*print;
	pthread_mutex_t			*eat_times;
	int						stop;
	int						*n_eat_times;
	unsigned int			last_eat;
	int						*dead;
	int						eat_index;
}					t_philo;

typedef struct s_all
{
	t_philo					*p;
	t_params				par;
	t_time					time;
	int						dead;
	int						n_eat_times;
	pthread_mutex_t			print;
	pthread_mutex_t			death;
	pthread_mutex_t			eat_times;
	pthread_t				supervisor;
}					t_all;

void			ft_putstr(char *str);
int				check_stop(t_all *all);
void			print_status(long int timestamp, int id, char *str, int dead);
void			ft_putlnbr(long int nb);
void			ft_putnbr(int nb);
void			ft_putchar(char c);
long int		get_time(void);
void			ft_usleep(long int time);
long int		get_tstamp(unsigned int ref);
int				ft_atoi(const char *str);
unsigned int	ft_atoui(const char *str);
int				is_digit(char *str);
int				parser(int argc, char **argv, t_params *par);
int				philosophers(t_params *par);
int				create_threads(int nb, t_all *all);
int				error_message(char *str);

#endif