#include "philo.h"

/*  ARGS:
    number_of_philo;
    time_to_die;
    time_to_eat;
    time_to_sleep;
    [n_times_philo_must_eat];
*/

void  ft_putstr(char *str)
{
  int i;

  i = 0;
  while (str[i])
    write(1, &(str[i++]), 1);
}

int	error_message(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	main(int argc, char **argv)
{
  t_params   par;

  par.n_times_eat = 0;
	if (argc < 5 || argc > 6)
		return(error_message("Error\nWrong number of arguments"));
	if (parser(argc, argv, &par))
		return(error_message("Error\nWrong arguments"));
//    printf("\t//ARGS//\nn_philo: %d\ntime_die: %d\ntime_eat: %d\ntime_sleep: %d\nn_times_eat: %d\n\t//ARGS//\n", par.n_philos, par.time_die, par.time_eat, par.time_sleep, par.n_times_eat);
	ft_putstr("before philosophers call\n");
  if (philosophers(&par))
		return(error_message("Error\nSomething went wrong during execution"));
}