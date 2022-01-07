/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:16:53 by melperri          #+#    #+#             */
/*   Updated: 2022/01/07 17:46:28 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int		ft_sleep(t_thread_info *philo)
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
	if (ft_print_mutex(philo->g, philo, SLEEP))
		return (-1);
	usleep(philo->g->time_to_sleep);
	return (0);
}

int	ft_eat(t_thread_info *philo)
{
	if (ft_is_philo_alive(philo) == 1)
		return (-1);
	if (ft_print_mutex(philo->g, philo, EAT))
		return (-1);
	usleep(philo->g->time_to_eat);
	philo->last_meal = philo->time_to_ret;
	philo->nb_meal_ate++;
	if (ft_sleep(philo))
		return (-1);
	return (0);
}

int	ft_lock_second_forks(t_thread_info *philo, int fork_id)
{
	pthread_mutex_lock(&philo->g->forks[fork_id].mutex);
	if (ft_is_philo_alive(philo) == 1)
		return (-1);
	if (ft_print_mutex(philo->g, philo, FORK))
		return (-1);
	if (ft_eat(philo))
		return (-1);
	return (0);
}

int	ft_lock_first_forks(t_thread_info *philo, int fork_id, int status)
{
	pthread_mutex_lock(&philo->g->forks[fork_id].mutex);
	if (ft_is_philo_alive(philo) == 1)
		return (-1);
	if (ft_print_mutex(philo->g, philo, FORK))
		return (-1);
	if (status == ODD)
	{
		if (philo->philo_id == 1)
		{
			if (ft_lock_second_forks(philo, 0))
				return (-1);
		}
		else
		{
			if (ft_lock_second_forks(philo, ++fork_id))
				return (-1);
		}
	}
	else
	{
		if (ft_lock_second_forks(philo, --fork_id))
			return (-1);
	}
	return (0);
}

int	ft_can_philo_lock_forks(t_thread_info *philo, int status)
{
	if (status == ODD)
	{
		if (philo->philo_id == 1)
		{
			if (ft_lock_first_forks(philo, philo->g->philo_nbr - 1, status))
				return (-1);
		}
		else if (philo->philo_id > 1)
		{
			if (ft_lock_first_forks(philo, philo->philo_id - 2, status))
				return (-1);
		}
	}
	else
	{
		if (ft_lock_first_forks(philo, philo->philo_id - 1, status))
			return (-1);
	}
	return (0);
}

int	ft_is_philo_even(int philo_id)
{
	return (philo_id % 2);
}
