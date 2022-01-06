/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:10:59 by melperri          #+#    #+#             */
/*   Updated: 2022/01/06 21:17:11 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_is_one_philo_dead(t_thread_info *philo)
{
	int	i;

	i = -1;
	while (++i < philo->g->philo_nbr)
	{
		if (philo->g->philo[i].dead == true)
			return (1);
	}
	return (0);
}

int	ft_is_philo_alive(t_thread_info *philo)
{
	if (ft_is_one_philo_dead(philo) == 1)
		return (1);
	get_real_time(philo->g->tv, philo);
	if ((int)philo->time_to_ret - philo->last_meal >= philo->g->time_to_die)
	{
		if (ft_print_mutex(philo->g, philo, DIE))
			return (-1);
		return (1);
	}
	else if (philo->nb_meal_ate >= philo->g->nb_max_meal)
	{
		if (ft_print_mutex(philo->g, philo, STOP))
			return (-1);
		return (1);
	}
	return (0);
}
