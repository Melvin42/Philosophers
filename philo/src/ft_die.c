/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:10:59 by melperri          #+#    #+#             */
/*   Updated: 2022/01/09 18:00:29 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitor_routine(void	*thread)
{
	t_env	*g;
	u_int64_t	sec;
	u_int64_t	usec;
	u_int64_t	time_to_ret;
	int	i;

	i = -1;
	g = (t_env *)thread;
	while (++i < g->philo_nbr)
	{
		pthread_mutex_lock(&g->last_meal_mutex);
		gettimeofday(&g->monitor_time, NULL);
		sec = (g->monitor_time.tv_sec - g->tv.tv_sec) * 1000000;
		usec = (g->monitor_time.tv_usec - g->tv.tv_usec);
		time_to_ret = (sec + usec) / 1000;
		if ((int)time_to_ret - g->philo[i].last_meal >= g->time_to_die)
		{
			pthread_mutex_lock(&g->run_mutex);
			ft_print_mutex(g, &g->philo[i], DIE);
			g->philo[i].alive = false;
			pthread_mutex_unlock(&g->run_mutex);
		}
		pthread_mutex_unlock(&g->last_meal_mutex);
		if (i == g->philo_nbr - 1)
		{
			i = -1;
			usleep(5000);
		}
	}
	return (&g->monitor);
}

//thread monitor, doit afficher la mort 10ms max apres l'heure de la mort.
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
