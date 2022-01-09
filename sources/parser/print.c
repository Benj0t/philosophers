/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:11:54 by bemoreau          #+#    #+#             */
/*   Updated: 2022/01/09 17:07:53 by bemoreau         ###   ########.fr       */
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
	if (nb >= 10)
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
	printf("%ld %d %s\n", timestamp, id, str);
}
