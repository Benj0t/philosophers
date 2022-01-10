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

void	print_status(long int timestamp, int id, char *str, int dead)
{
	int	i;

	i = 0;
	if (dead == 1)
		return ;
	printf("%ld %u %s\n", timestamp, id + 1, str);
}
