/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:16:58 by melperri          #+#    #+#             */
/*   Updated: 2022/01/05 22:58:05 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	get_real_time(struct timeval tv_start, t_thread_info *philo)
{
	u_int64_t	sec;
	u_int64_t	usec;

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
	while (1)
	{
		get_real_time(philo->g->tv, philo);
		if (philo->g->run == 1)
			break ;
		if ((int)philo->time_to_ret - philo->last_meal > philo->g->time_to_die)
		{
			if (ft_print_mutex(philo->g, philo, DIE))
				return (NULL);
			break ;
		}
		else if (philo->nb_meal_ate  >= philo->g->nb_max_meal)
		{
			if (ft_print_mutex(philo->g, philo, DIE))
				return (NULL);
			break ;
		}
		if (ft_is_philo_even(philo))
			ft_eat(philo);
		else if (philo->is_thinking == 0)
		{
			ft_think(philo);
			philo->is_thinking = 1;
		}
		usleep(2000);
	}
	return (philo);
}

int	main(int ac, char **av)
{
	t_env			g;
	t_thread_info	*philo;

	philo = NULL;
	if (ac < 5 || ac > 6)
		return (write(1, ARG_ERROR, sizeof(ARG_ERROR)));
	if (av[1][0] == '0')
		return (0);
	ft_get_args(av, &g);
	if (ft_check_args(ac, av))
		return (write(1, ARG_ERROR, sizeof(ARG_ERROR)));
	if (ft_program(&philo, &g))
		return (ft_free_all(&philo));
	ft_free_all(&philo);
	return (0);
}
