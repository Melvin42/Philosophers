/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:16:58 by melperri          #+#    #+#             */
/*   Updated: 2022/01/08 16:58:05 by melperri         ###   ########.fr       */
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
			usleep(20);
			ft_can_philo_lock_forks(philo, EVEN);
		}
		else
			ft_can_philo_lock_forks(philo, ODD);
		usleep(500);
	}
}

void	*thread_start(void *thread)
{
	t_thread_info	*philo;

	philo = (t_thread_info *)thread;
	while (philo->alive)
	{
		ft_is_philo_alive(philo, THINK);
		ft_actions(philo);
	}
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
