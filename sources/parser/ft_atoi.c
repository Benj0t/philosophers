/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:11:40 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/16 10:13:33 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int		ft_iswhspaces(int ch)
{
	if ((ch <= 13 && ch >= 9) || ch == 32)
		return (1);
	return (0);
}

static int      ft_isdigit(char c)
{
    if (c <= '9' && c >= '0')
        return (1);
    return (0);
}

int				ft_atoi(const char *str)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (ft_iswhspaces(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		nb = nb * 10 + (str[i++] - 48);
	return (nb);
}

unsigned int	ft_atoui(const char *str)
{
	int i;
	unsigned int nb;

	i = 0;
	nb = 0;
	while (ft_iswhspaces(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		nb = nb * 10 + (str[i++] - 48);
	return (nb);
}