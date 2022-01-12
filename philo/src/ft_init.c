/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:53:00 by melperri          #+#    #+#             */
/*   Updated: 2022/01/12 15:57:39 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

static int	ft_init_philo(t_thread_info **philo, t_env *g)
{
	int	i;

	i = -1;
	g->run = true;
	g->philo = *philo;
	while (++i < g->philo_nbr)
	{
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].g = g;
		(*philo)[i].alive = true;
		(*philo)[i].nb_meal_ate = 0;
		if (pthread_mutex_init(&g->forks[i].mutex, NULL) == -1)
			return (-1);
		if (pthread_mutex_init(&(*philo)[i].last_meal_mutex, NULL) == -1)
			return (-1);
	}
	if (pthread_mutex_init(&g->run_mutex, NULL) == -1)
		return (-1);
	return (0);
}

int	ft_create_thread(t_thread_info **philo, t_env *g)
{
	int	i;

	i = -1;
	while (++i < g->philo_nbr)
	{
		if (pthread_create(&(*philo)[i].thread_id,
				NULL, &thread_start, &(*philo)[i]))
			return (-1);
		usleep(20);
	}
	if (pthread_create(&g->monitor,
			NULL, &monitor_routine, g))
		return (-1);
	return (0);
}

static int	ft_malloc_philo(t_thread_info **philo, t_env *g)
{
	int	i;

	if (ft_malloc_simple((void **)philo, sizeof(**philo), g->philo_nbr))
		return (-1);
	i = -1;
	while (++i < g->philo_nbr)
		memset(&(*philo)[i], 0, sizeof(t_thread_info));
	if (ft_malloc_simple((void **)&g->forks, sizeof(*g->forks), g->philo_nbr))
		return (-1);
	return (0);
}

static int	ft_join_thread(t_thread_info **philo, t_env *g)
{
	int	i;

	i = -1;
	(void)philo;
	while (++i < g->philo_nbr)
	{
		if (pthread_join((*philo)[i].thread_id, NULL))
			return (-1);
	}
	if (pthread_join(g->monitor, NULL))
		return (-1);
	return (0);
}

int	ft_program(t_thread_info **philo, t_env *g)
{
	if (ft_malloc_philo(philo, g) == -1)
		return (-1);
	if (ft_init_philo(philo, g) == -1)
		return (-1);
	if (gettimeofday(&g->tv, NULL) < 0)
		return (-1);
	if (ft_create_thread(philo, g) == -1)
		return (-1);
	if (ft_join_thread(philo, g) == -1)
		return (-1);
	return (0);
}
