#include "philo.h"

/*  ARGS:
    number_of_philo;
    time_to_die;
    time_to_eat;
    time_to_sleep;
    [n_times_philo_must_eat];
*/

int	error_message(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	main(int argc, char **argv)
{
  t_params  par;
  t_data    data;

  data.forks = NULL;
  data.philo = NULL;
	if (argc < 5 || argc > 6)
		return(error_message("Error\nWrong number of arguments"));
	if (parser(argc, argv, &par))
		return(error_message("Error\nWrong arguments"));
//    printf("\t//ARGS//\nn_philo: %d\ntime_die: %d\ntime_eat: %d\ntime_sleep: %d\nn_times_eat: %d\n\t//ARGS//\n", par.n_philos, par.time_die, par.time_eat, par.time_sleep, par.n_times_eat);
  if (philosophers(&par, &data))
		return(error_message("Error\nSomething went wrong during execution"));
}