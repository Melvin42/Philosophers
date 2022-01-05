/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:16:58 by melperri          #+#    #+#             */
/*   Updated: 2022/01/05 17:34:17 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_get_args(char **av, t_env *g)
{
	if (av[1])
		g->philo_nbr = ft_atoi(av[1]);
	if (av[2])
		g->time_to_die = ft_atoi(av[2]);
	if (av[3])
		g->time_to_eat = ft_atoi(av[3]);
	if (av[4])
		g->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		g->nb_max_meal = ft_atoi(av[5]);
	else
		g->nb_max_meal = INT_MAX;
}

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

static void	*thread_start(void *thread)
{
	t_thread_info	*philo;

	philo = (t_thread_info *)thread;
	while (1)
	{
		get_real_time(philo->g->tv, philo);
		if ((int)philo->time_to_ret - philo->last_meal > philo->g->time_to_die)
		{
			printf("%ld %d %s\n", philo->time_to_ret, philo->philo_id, STR_DIE);
			//remplacer exit par le monitoring
			exit(0);
		}
		else if (philo->nb_meal_ate  >= philo->g->nb_max_meal)
		{
			printf("%ld %d %s\n", philo->time_to_ret, philo->philo_id, STR_DIE);
			//remplacer exit par le monitoring
			exit(0);
		}
		if (ft_is_philo_even(philo))
		{
			ft_eat(philo);
		}
		else if (philo->is_thinking == 0)
		{
			ft_think(philo);
			philo->is_thinking = 1;
		}
		usleep(2000);
	}
	return (philo);
}

static int	ft_create_thread(t_thread_info **philo, t_env *g)
{
	int	tnum;

	if (ft_malloc_simple((void **)philo, sizeof(**philo), g->philo_nbr))
		return (-1);
	tnum = -1;
	while (++tnum < g->philo_nbr)
		memset(&(*philo)[tnum], 0, sizeof(t_thread_info));
	if (ft_malloc_simple((void **)&g->forks, sizeof(*g->forks), g->philo_nbr))
		return (-1);
	tnum = -1;
	while (++tnum < g->philo_nbr)
	{
		(*philo)[tnum].philo_id = tnum + 1;
		(*philo)[tnum].g = g;
		(*philo)[tnum].nb_meal_ate = 0;
		if (pthread_mutex_init(&g->forks[tnum].mutex, NULL) == -1)
			return (-1);
	}
	if (pthread_mutex_init(&g->print_mutex, NULL) == -1)
		return (-1);
	if (gettimeofday(&g->tv, NULL) < 0)
	{
		if (pthread_mutex_init(&g->forks[tnum].mutex, NULL) == -1)
			return (-1);
	}
	if (gettimeofday(&g->tv, NULL) < 0)
		return (-1);
	tnum = -1;
	while (++tnum < g->philo_nbr)
	{
		usleep(20);
		if (pthread_create(&(*philo)[tnum].thread_id,
				NULL, &thread_start, &(*philo)[tnum]))
			return (-1);
	}
	tnum = -1;
	while (++tnum < g->philo_nbr)
	{
		if (pthread_join((*philo)[tnum].thread_id, NULL))
			return (ft_free_all(philo));
	}
	return (0);
}

//refuser le arguments negatif
int	main(int ac, char **av)
{
	t_env			g;
	t_thread_info	*philo;

	philo = NULL;
	if (ac < 5 || ac > 6)
		return (write(1, ARG_ERROR, sizeof(ARG_ERROR)));
	ft_get_args(av, &g);;
	if (ft_create_thread(&philo, &g))
		return (-1);
	ft_free_all(&philo);
	return (0);
}
