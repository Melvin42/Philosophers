/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_int_max.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:24:40 by melperri          #+#    #+#             */
/*   Updated: 2022/01/26 20:24:58 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static long	ft_atol(const char *nptr)
{
	unsigned long	res;
	long			sign;

	res = 0;
	sign = 1;
	while (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		res = res * 10 + (*nptr - 48);
		nptr++;
	}
	if (res > LLONG_MAX && sign == -1)
		return (0);
	else if (res > LLONG_MAX && sign == 1)
		return (-1);
	return (res * sign);
}

int	ft_check_int_max(char **av)
{
	int		i;
	long	min;
	long	max;
	long	nbr;

	min = INT_MIN;
	max = INT_MAX;
	i = 0;
	while (av[++i])
	{
		if (ft_strlen(av[i]) > 11)
			return (-1);
		nbr = ft_atol(av[i]);
		if (nbr > max || nbr < min)
			return (-1);
	}
	return (0);
}
