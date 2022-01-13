/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:10:59 by melperri          #+#    #+#             */
/*   Updated: 2022/01/13 19:46:45 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static u_int64_t	get_time_routine(t_env *g)
{
	u_int64_t	sec;
	u_int64_t	usec;

	gettimeofday(&g->monitor_time, NULL);
	sec = (g->monitor_time.tv_sec - g->tv.tv_sec) * 1000000;
	usec = (g->monitor_time.tv_usec - g->tv.tv_usec);
	return ((sec + usec) / 1000);
}

void	*monitor_routine(void	*thread)
{
	t_env		*g;
	u_int64_t	time_to_ret;
	int			i;

	i = -1;
	g = (t_env *)thread;
	time_to_ret = 0;
	while (++i < g->philo_nbr)
	{
		pthread_mutex_lock(&g->philo[i].last_meal_mutex);
		time_to_ret = get_time_routine(g);
		if ((int)time_to_ret - g->philo[i].last_meal > g->time_to_die)
		{
			pthread_mutex_unlock(&g->philo[i].last_meal_mutex);
			ft_print_mutex(g, &g->philo[i], DIE);
			return (&g->monitor);
		}
		pthread_mutex_unlock(&g->philo[i].last_meal_mutex);
		if (i == g->philo_nbr - 1)
		{
			i = -1;
			usleep(5000);
		}
	}
	return (&g->monitor);
}

void	ft_is_philo_alive(t_thread_info *philo, int status)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	get_real_time(philo->g->tv, philo);
	if ((int)philo->time_to_ret - philo->last_meal > philo->g->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_meal_mutex);
		ft_print_mutex(philo->g, philo, DIE);
		pthread_mutex_lock(&philo->alive_mutex);
		philo->alive = false;
		pthread_mutex_unlock(&philo->alive_mutex);
	}
	else if (philo->nb_meal_ate >= philo->g->nb_max_meal)
	{
		pthread_mutex_unlock(&philo->last_meal_mutex);
		ft_print_mutex(philo->g, philo, STOP);
		pthread_mutex_lock(&philo->alive_mutex);
		philo->alive = false;
		pthread_mutex_unlock(&philo->alive_mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->last_meal_mutex);
		ft_print_mutex(philo->g, philo, status);
	}
}
