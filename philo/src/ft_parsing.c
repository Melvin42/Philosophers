/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:38:33 by melperri          #+#    #+#             */
/*   Updated: 2022/01/13 19:35:16 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_zero(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != '0')
			break ;
	}
	if (i == ft_strlen(s))
		return (1);
	else
		return (0);
}

void	ft_get_args(char **av, t_env *g)
{
	if (av[1])
		g->philo_nbr = ft_atoi(av[1]);
	if (av[2])
		g->time_to_die = ft_atoi(av[2]);
	if (av[3])
		g->time_to_eat = ft_atoi(av[3]) * 1000;
	if (av[4])
		g->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		g->nb_max_meal = ft_atoi(av[5]);
	else
		g->nb_max_meal = INT_MAX;
}

static int	ft_bad_arg(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (-1);
	}
	return (0);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (ft_bad_arg(av[i]))
			return (-1);
	}
	return (0);
}
