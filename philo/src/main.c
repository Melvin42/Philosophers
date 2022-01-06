/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:16:58 by melperri          #+#    #+#             */
/*   Updated: 2022/01/06 06:07:50 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	get_real_time(struct timeval tv_start, t_thread_info *philo)
{
	u_int64_t	sec;
	u_int64_t	usec;

// enlever perror
	if (gettimeofday(&philo->tv, NULL) < 0)
		perror("gettimeofday failed");
	sec = (philo->tv.tv_sec - tv_start.tv_sec) * 1000000;
	usec = (philo->tv.tv_usec - tv_start.tv_usec);
	philo->time_to_ret = (sec + usec) / 1000;
}

void	*thread_start(void *thread)
{
	t_thread_info	*philo;

	philo = (t_thread_info *)thread;
	if (ft_print_mutex(philo->g, philo, THINK))
		return (NULL);
	while (1)
	{
		if (philo->g->run == 1)
			break ;
		get_real_time(philo->g->tv, philo);
		if ((int)philo->time_to_ret - philo->last_meal >= philo->g->time_to_die)
		{
			if (ft_print_mutex(philo->g, philo, DIE))
				return (NULL);
			break ;
		}
		else if (philo->nb_meal_ate >= philo->g->nb_max_meal)
		{
			if (ft_print_mutex(philo->g, philo, STOP))
				return (NULL);
			break ;
		}
		if (philo->g->philo_nbr > 1)
		{
			if (!ft_is_philo_even(philo->philo_id))
			{
				usleep(20);
				if (ft_can_philo_lock_forks(philo, EVEN))
					return (NULL);
			}
			else
			{
				if (ft_can_philo_lock_forks(philo, ODD))
					return (NULL);
			}
			if (ft_print_mutex(philo->g, philo, THINK))
				return (NULL);
			usleep(500);
		}
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
