/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:16:53 by melperri          #+#    #+#             */
/*   Updated: 2022/01/13 19:54:06 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_unlock(t_thread_info *philo)
{
	if (philo->philo_id == 1)
	{
		pthread_mutex_unlock(&(philo->g->forks[philo->g->philo_nbr - 1]).mutex);
		pthread_mutex_unlock(&(philo->g->forks[0]).mutex);
	}
	else if (philo->philo_id > 1)
	{
		pthread_mutex_unlock(&(philo->g->forks[philo->philo_id - 2]).mutex);
		pthread_mutex_unlock(&(philo->g->forks[philo->philo_id - 1]).mutex);
	}
}

void	ft_lock_second_forks(t_thread_info *philo, int fork_id)
{
	pthread_mutex_lock(&philo->g->forks[fork_id].mutex);
	ft_is_philo_alive(philo, FORK);
	ft_eat(philo);
}

void	ft_lock_first_forks(t_thread_info *philo, int fork_id, int status)
{
	pthread_mutex_lock(&philo->g->forks[fork_id].mutex);
	ft_is_philo_alive(philo, FORK);
	if (status == ODD)
	{
		if (philo->philo_id == 1)
			ft_lock_second_forks(philo, philo->g->philo_nbr - 1);
		else
			ft_lock_second_forks(philo, ++fork_id);
	}
	else
		ft_lock_second_forks(philo, --fork_id);
}

void	ft_can_philo_lock_forks(t_thread_info *philo, int status)
{
	if (status == ODD)
	{
		if (philo->philo_id == 1)
			ft_lock_first_forks(philo, 0, status);
		else if (philo->philo_id > 1)
			ft_lock_first_forks(philo, philo->philo_id - 2, status);
	}
	else
	{
		ft_lock_first_forks(philo, philo->philo_id - 1, status);
	}
}
