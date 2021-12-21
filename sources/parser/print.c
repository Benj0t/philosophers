/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:11:54 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/21 15:47:56 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb > 10)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + 48);
}

void	ft_putlnbr(long int nb)
{
	if (nb > 10)
		ft_putlnbr(nb / 10);
	ft_putchar(nb % 10 + 48);
}

void	print_status(long int timestamp, int id, char *str, int dead)
{
	int	i;

	i = 0;
	(void)dead;
	if (dead == 1)
		return ;
	ft_putlnbr(timestamp);
	write(1, " ", 1);
	ft_putnbr(id);
	write(1, " ", 1);
	while (str[i])
	{
		write(1, &str[i++], 1);
	}
	write(1, "\n", 1);
}
