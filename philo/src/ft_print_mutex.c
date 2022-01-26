/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:38:43 by melperri          #+#    #+#             */
/*   Updated: 2022/01/26 23:51:18 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_set_alive_mutex_false(t_thread_info *philo)
{
	pthread_mutex_lock(&philo->alive_mutex);
	philo->alive = false;
	pthread_mutex_unlock(&philo->alive_mutex);
}

static int	ft_check_run(t_thread_info *philo)
{
	if (philo->g->run == false)
	{
		ft_set_alive_mutex_false(philo);
		return (1);
	}
	else
		return (0);
}

static void	ft_write_action(int action, t_thread_info *philo)
{
	if (ft_check_run(philo))
		return ;
	if (action == FORK)
		printf("%lu %d %s", philo->time_to_ret, philo->philo_id, STR_FORK);
	else if (action == EAT)
		printf("%lu %d %s", philo->time_to_ret, philo->philo_id, STR_EAT);
	else if (action == SLEEP)
		printf("%lu %d %s", philo->time_to_ret, philo->philo_id, STR_SLEEP);
	else if (action == THINK)
		printf("%lu %d %s", philo->time_to_ret, philo->philo_id, STR_THINK);
	else if (action == DIE)
	{
		philo->g->run = false;
		printf("%lu %d %s", philo->time_to_ret, philo->philo_id, STR_DIE);
	}
	else if (action == STOP)
		ft_set_alive_mutex_false(philo);
}

void	ft_print_mutex(t_env *g, t_thread_info *philo, int action)
{
	pthread_mutex_lock(&g->run_mutex);
	get_real_time(philo->g->tv, philo);
	ft_write_action(action, philo);
	pthread_mutex_unlock(&g->run_mutex);
}
