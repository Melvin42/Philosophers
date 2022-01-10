/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:58:40 by melperri          #+#    #+#             */
/*   Updated: 2022/01/10 16:46:24 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
static void	ft_is_one_philo_dead(t_thread_info *philo)
{
	get_real_time(philo->g->tv, philo);
//	printf("ret = %lu\n", philo->time_to_ret);
//	printf("last meal = %d\n", philo->last_meal);
//	printf("time to die = %d\n", philo->g->time_to_die);
//	printf("ret = %lu\n", philo->time_to_ret);
//	pthread_mutex_lock(&philo->g->last_meal_mutex);
	if ((int)philo->time_to_ret - philo->last_meal >= philo->g->time_to_die +10)
	{
//		pthread_mutex_unlock(&philo->g->last_meal_mutex);
		ft_print_mutex(philo->g, philo, DIE);
		philo->alive = false;
	}
//	else if (philo->nb_meal_ate >= philo->g->nb_max_meal)
//	{
//		pthread_mutex_unlock(&philo->g->last_meal_mutex);
//		ft_print_mutex(philo->g, philo, STOP);
//		philo->alive = false;
//	}
}
*/

void	ft_usleep(t_thread_info *philo, int time_to_wait)
{
	int	i;
	u_int64_t old_time;

	i = -1;
	get_real_time(philo->g->tv, philo);
	old_time = philo->time_to_ret;
//	while (++i < time / 5000)
	while ((int)philo->time_to_ret - (int)old_time < time_to_wait)//philo->last_meal >= philo->g->time_to_die)
	{
		get_real_time(philo->g->tv, philo);
		if ((int)philo->time_to_ret - philo->last_meal >= philo->g->time_to_die)
		{
	//		pthread_mutex_unlock(&philo->g->last_meal_mutex);
			ft_print_mutex(philo->g, philo, DIE);
			philo->alive = false;
		}
//		printf("ASDFG\n");
//		ft_is_one_philo_dead(philo);
		usleep(5000);
	}
}
