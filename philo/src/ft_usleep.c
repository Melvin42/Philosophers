/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:58:40 by melperri          #+#    #+#             */
/*   Updated: 2022/01/12 16:41:01 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_usleep(t_thread_info *philo, int time_to_wait)
{
	int	i;
	u_int64_t old_time;

	i = -1;
	get_real_time(philo->g->tv, philo);
	old_time = philo->time_to_ret;
	time_to_wait /= 1000;
	while ((int)philo->time_to_ret - (int)old_time < time_to_wait)//philo->last_meal >= philo->g->time_to_die)
	{
		pthread_mutex_lock(&philo->last_meal_mutex);
		get_real_time(philo->g->tv, philo);
		if ((int)philo->time_to_ret - philo->last_meal >= philo->g->time_to_die)
		{
			pthread_mutex_unlock(&philo->last_meal_mutex);
//			ft_print_mutex(philo->g, philo, DIE);
			philo->alive = false;
			break ;
		}
		pthread_mutex_unlock(&philo->last_meal_mutex);
		usleep(500);
	}
}
