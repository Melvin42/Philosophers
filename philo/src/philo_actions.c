/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:16:53 by melperri          #+#    #+#             */
/*   Updated: 2022/01/09 18:00:22 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_sleep(t_thread_info *philo)
{
	if (philo->philo_id == 1)
	{
		pthread_mutex_unlock(&(philo->g->forks[philo->g->philo_nbr - 1]).mutex);
		pthread_mutex_unlock(&(philo->g->forks[0]).mutex);
	}
	else if (philo->philo_id > 1)
	{
		if (ft_is_philo_even(philo->philo_id))
		{
			pthread_mutex_unlock(&(philo->g->forks[philo->philo_id - 2]).mutex);
			pthread_mutex_unlock(&(philo->g->forks[philo->philo_id - 1]).mutex);
		}
		else
		{
			pthread_mutex_unlock(&(philo->g->forks[philo->philo_id - 1]).mutex);
			pthread_mutex_unlock(&(philo->g->forks[philo->philo_id - 2]).mutex);
		}
	}
	ft_is_philo_alive(philo, SLEEP);
	ft_usleep(philo, philo->g->time_to_sleep);
}

void	ft_eat(t_thread_info *philo)
{
	ft_is_philo_alive(philo, EAT);
	pthread_mutex_lock(&philo->g->last_meal_mutex);
	philo->last_meal = philo->time_to_ret;
	philo->nb_meal_ate++;
	pthread_mutex_unlock(&philo->g->last_meal_mutex);
	ft_usleep(philo, philo->g->time_to_eat);
	ft_sleep(philo);
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
			ft_lock_second_forks(philo, 0);
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
			ft_lock_first_forks(philo, philo->g->philo_nbr - 1, status);
		else if (philo->philo_id > 1)
			ft_lock_first_forks(philo, philo->philo_id - 2, status);
	}
	else
		ft_lock_first_forks(philo, philo->philo_id - 1, status);
}

int	ft_is_philo_even(int philo_id)
{
	return (philo_id % 2);
}
