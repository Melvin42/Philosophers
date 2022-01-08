/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:10:59 by melperri          #+#    #+#             */
/*   Updated: 2022/01/08 17:36:49 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_is_one_philo_dead(t_thread_info *philo)
{
	int	i;

//	pthread_mutex_lock(&philo->g->monitor_mutex);
	i = -1;
	get_real_time(philo->g->tv, philo);
	while (++i < philo->g->philo_nbr)
	{
		if ((int)philo->time_to_ret - philo->g->philo[i].last_meal >= philo->g->time_to_die)
		{
//			philo->g->run = false;
//			ft_print_mutex(philo->g, &philo->g->philo[i], DIE);
		}
	}
//	pthread_mutex_unlock(&philo->g->monitor_mutex);
}
// thread monitor, doit afficher la mort 10ms max apres l'heure de la mort.
//philo 5 210 100 200 4
void	ft_is_philo_alive(t_thread_info *philo, int status)
{
	get_real_time(philo->g->tv, philo);
	if ((int)philo->time_to_ret - philo->last_meal >= philo->g->time_to_die)
	{
		ft_print_mutex(philo->g, philo, DIE);
		philo->alive = false;
	}
	else if (philo->nb_meal_ate >= philo->g->nb_max_meal)
	{
		ft_print_mutex(philo->g, philo, STOP);
		philo->alive = false;
	}
	else
		ft_print_mutex(philo->g, philo, status);
}
