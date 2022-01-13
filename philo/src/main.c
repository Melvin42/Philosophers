/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:16:58 by melperri          #+#    #+#             */
/*   Updated: 2022/01/13 19:50:12 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	get_real_time(struct timeval tv_start, t_thread_info *philo)
{
	u_int64_t	sec;
	u_int64_t	usec;

	gettimeofday(&philo->tv, NULL);
	sec = (philo->tv.tv_sec - tv_start.tv_sec) * 1000000;
	usec = (philo->tv.tv_usec - tv_start.tv_usec);
	philo->time_to_ret = (sec + usec) / 1000;
}

static void	ft_actions(t_thread_info *philo)
{
	if (philo->g->philo_nbr > 1)
	{
		if (!ft_is_philo_even(philo->philo_id))
		{
			usleep(100);
			ft_can_philo_lock_forks(philo, EVEN);
		}
		else
		{
			ft_can_philo_lock_forks(philo, ODD);
		}
	}
}

static void	ft_think(t_thread_info *philo)
{
	if (philo->g->philo_nbr % 2 == 0)
		ft_is_philo_alive(philo, THINK);
	else
	{
		ft_is_philo_alive(philo, THINK);
		if (ft_is_philo_even(philo->philo_id))
			usleep(5000);
	}
}

void	*thread_start(void *thread)
{
	t_thread_info	*philo;

	philo = (t_thread_info *)thread;
	if (philo->g->philo_nbr == 1)
	{
		ft_print_mutex(philo->g, philo, THINK);
		ft_usleep(philo, philo->g->time_to_die);
		return (philo);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->alive_mutex);
		if (philo->alive == false)
			break ;
		pthread_mutex_unlock(&philo->alive_mutex);
		ft_actions(philo);
		ft_think(philo);
	}
	pthread_mutex_unlock(&philo->alive_mutex);
	return (philo);
}

int	main(int ac, char **av)
{
	t_env			g;
	t_thread_info	*philo;

	if (ac < 5 || ac > 6)
		return (write(1, ARG_ERROR, sizeof(ARG_ERROR)));
	if (ft_zero(av[1]))
		return (0);
	philo = NULL;
	memset(&g, 0, sizeof(g));
	ft_get_args(av, &g);
	if (ft_check_args(ac, av))
		return (write(1, ARG_ERROR, sizeof(ARG_ERROR)));
	if (ft_program(&philo, &g))
		return (ft_free_all(&philo));
	ft_free_all(&philo);
	return (0);
}
