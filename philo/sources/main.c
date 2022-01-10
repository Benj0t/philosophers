/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:11:04 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/21 15:45:23 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr(char *str)
{
	int	i;

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
	t_params	par;

	par.n_times_eat = 0;
	if (argc < 5 || argc > 6)
		return (error_message("Error\nWrong number of arguments"));
	if (parser(argc, argv, &par))
		return (error_message("Error\nWrong arguments"));
	if (philosophers(&par))
		return (error_message("Error\nSomething went wrong during execution"));
}
