/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:58:40 by melperri          #+#    #+#             */
/*   Updated: 2022/01/09 17:59:06 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_is_one_philo_dead(t_thread_info *philo)
{
//	int	i;

//	i = -1;
//	while (++i < philo->g->philo_nbr)
//	{
		get_real_time(philo->g->tv, philo);
		if ((int)philo->time_to_ret - philo->last_meal >= philo->g->time_to_die)
		{
			ft_print_mutex(philo->g, philo, DIE);
//			printf("SDFGH\n");
			philo->alive = false;
		}
		else if (philo->nb_meal_ate >= philo->g->nb_max_meal)
		{
			ft_print_mutex(philo->g, philo, STOP);
			philo->alive = false;
		}
//	}
}
void	ft_usleep(t_thread_info *philo, int time)
{
	int	i;

	i = -1;
	while (++i < time / 2000)
	{
		ft_is_one_philo_dead(philo);
		usleep(2000);
	}
}
