#include "philo.h"

void    ft_putendl(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i++], 1);
	}
	write(1, "\n", 1);
}

int     is_digit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] <= '9' && str[i] >= '0') && str[i] != '+')
            return (1); 
        i++;
    }
    return (0);
}