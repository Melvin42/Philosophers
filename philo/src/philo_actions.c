/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:16:53 by melperri          #+#    #+#             */
/*   Updated: 2022/01/05 19:46:18 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_take_forks(t_thread_info *philo, int fork_id)
{
	if (pthread_mutex_lock(&philo->g->forks[fork_id].mutex) == -1)
	{
		perror("Mutex lock failed");
		exit(1);
	}
	get_real_time(philo->g->tv, philo);
	philo->is_thinking = 1;
	if (ft_print_mutex(philo->g, philo, FORK))
		return ;
}

void	ft_think(t_thread_info *philo)
{
	get_real_time(philo->g->tv, philo);
	ft_print_mutex(philo->g, philo, THINK);
}

void	ft_sleep(t_thread_info *philo)
{
	get_real_time(philo->g->tv, philo);
	ft_print_mutex(philo->g, philo, SLEEP);
	usleep(philo->g->time_to_sleep);
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

void	ft_eat(t_thread_info *philo)
{
	get_real_time(philo->g->tv, philo);
	ft_print_mutex(philo->g, philo, EAT);
	philo->last_meal = philo->time_to_ret;
	philo->nb_meal_ate++;
	usleep(philo->g->time_to_eat);
	ft_sleep(philo);
}

int	ft_can_philo_take_forks(t_thread_info *philo, int status)
{
	if (status == ODD)
	{
		if (philo->philo_id == 1)
		{
			ft_take_forks(philo, philo->g->philo_nbr - 1);
			ft_take_forks(philo, 0);
			return (1);
		}
		else if (philo->philo_id > 1)
		{
			ft_take_forks(philo, philo->philo_id - 2);
			ft_take_forks(philo, philo->philo_id - 1);
			return (1);
		}
	}
	else
	{
		usleep(20);
		ft_take_forks(philo, philo->philo_id - 1);
		ft_take_forks(philo, philo->philo_id - 2);
		return (1);
	}
	return (0);
}

int	ft_is_philo_even(t_thread_info *philo)
{
	if ((philo->philo_id - 1) % 2 == 0)
	{
		return (ft_can_philo_take_forks(philo, ODD));
	}
	else
	{
		usleep(20);
		return (ft_can_philo_take_forks(philo, EVEN));
	}
	return (0);
}
