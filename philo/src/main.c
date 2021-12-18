/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:16:58 by melperri          #+#    #+#             */
/*   Updated: 2021/12/18 17:40:05 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                          void *(*start_routine) (void *), void *arg);
//int gettimeofday(struct timeval *tv, struct timezone *tz);
//int pthread_join(pthread_t thread, void **retval);
//int pthread_detach(pthread_t thread);
//int pthread_mutex_init(pthread_mutex_t *restrict mutex,
//      const pthread_mutexattr_t *restrict attr);
//int pthread_mutex_destroy(pthread_mutex_t *mutex);

//	pthread_detach();
//	pthread_mutex_lock();
//	pthread_mutex_unlock();
static void	ft_free(void **tofree)
{
	if (*tofree)
	{
		free(*tofree);
		*tofree = NULL;
	}
}

static int	ft_free_all(t_thread_info **philo)
{
	ft_free((void **)philo);
	return (-1);
}

static int	ft_malloc_simple(void **var, size_t n, int size)
{
	*var = malloc(n * size);
	if (!*var)
		return (-1);
	memset(*var, 0, n);
	return (0);
}

static void	*thread_start(void *thread)
{
	t_thread_info	*philo;

	philo = (t_thread_info *)thread;
	if (gettimeofday(&philo->tv, NULL) < 0)
		perror("gettimeofday failed");
	printf("%ld %d %s\n", philo->tv.tv_sec, philo->thread_num, FORK);
	return (philo);
}

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
		g->time_to_die = ft_atoi(av[5]);
	if (av[6])
		g->nbr_of_each_philo_must_eat = ft_atoi(av[6]);
}

static int	ft_create_thread(t_thread_info **philo, t_env *g)
{
	int	tnum;

	if (ft_malloc_simple((void **)philo, sizeof(**philo), g->philo_nbr))
		return (-1);
	tnum = -1;
	while (++tnum < g->philo_nbr)
	{
		(*philo)[tnum].thread_num = tnum + 1;
		if (pthread_create(&(*philo)[tnum].thread_id,
				NULL, &thread_start, (void *)&(*philo)[tnum]))
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

int	main(int ac, char **av)
{
	t_env			g;
	t_thread_info	*philo;

	if (ac < 5 || ac > 6)
		return (write(1, ARG_ERROR, sizeof(ARG_ERROR)));
	ft_get_args(av, &g);
	if (ft_create_thread(&philo, &g))
		return (-1);
	ft_free_all(&philo);
	return (0);
}
