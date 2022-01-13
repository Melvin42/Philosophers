/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:53:30 by melperri          #+#    #+#             */
/*   Updated: 2022/01/13 19:55:21 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_sleep(t_thread_info *philo)
{
	ft_is_philo_alive(philo, SLEEP);
	ft_unlock(philo);
	ft_usleep(philo, philo->g->time_to_sleep);
}

void	ft_eat(t_thread_info *philo)
{
	ft_is_philo_alive(philo, EAT);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = philo->time_to_ret;
	philo->nb_meal_ate++;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ft_usleep(philo, philo->g->time_to_eat);
	ft_sleep(philo);
}
