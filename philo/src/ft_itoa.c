/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:51:38 by melperri          #+#    #+#             */
/*   Updated: 2022/01/05 18:01:08 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

static int	ft_abs_nb(int n)
{
	if (n < 0)
		return (n * -1);
	else
		return (n);
}

static int	ft_calc_len(int n)
{
	if (n < 0)
		return (2);
	else
		return (1);
}

char	*ft_itoa(int n)
{
	char	*s;
	long	nb;
	int		len;

	nb = ft_abs_nb(n);
	len = ft_calc_len(n);
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	s[len] = '\0';
	nb = ft_abs_nb(n);
	while (len - 1 >= 0)
	{
		s[len - 1] = nb % 10 + 48;
		nb = nb / 10;
		len--;
	}
	if (n < 0)
		s[0] = '-';
	return (s);
}
