/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:16:58 by melperri          #+#    #+#             */
/*   Updated: 2021/12/18 14:31:29 by melperri         ###   ########.fr       */
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
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void	ft_free(void **tofree)
{
	if (*tofree)
	{
		free(*tofree);
		*tofree = NULL;
	}
}

static int	ft_free_all(t_env *g, t_thread_info **philo)
{
	(void)g;
//	ft_free((void **)&philo[0]->thread_id);
	ft_free((void **)philo);
	return (-1);
}

static int	ft_malloc_simple(void **var, size_t n, int size)
{
	*var = malloc(n * size);
	if (!*var)
	{
		perror("malloc failed");
		return (-1);
	}
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

int	main(int ac, char **av)
{
	t_env			g;
	t_thread_info	*philo;
//	pthread_mutex_t	*mutex;
	int				tnum;

	if (ac < 5 || ac > 6)
	{
		write(1, ARG_ERROR, sizeof(ARG_ERROR));
		return (-1);
	}
//	mutex = NULL;
	if (av[1])
		g.philo_nbr = ft_atoi(av[1]);
	if (av[2])
		g.time_to_die = ft_atoi(av[2]);
	if (av[3])
		g.time_to_eat = ft_atoi(av[3]);
	if (av[4])
		g.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		g.time_to_die = ft_atoi(av[5]);
	if (av[6])
		g.nbr_of_each_philo_must_eat = ft_atoi(av[6]);
	philo = NULL;
	g.philo_nbr = 1;
	if (ft_malloc_simple((void **)&philo, sizeof(*philo), g.philo_nbr))
		return (-1);
	if (gettimeofday(&philo[0].tv, NULL) < 0)
		perror("gettimeofday failed");
	tnum = -1;
	while (++tnum < g.philo_nbr)
	{
		if (pthread_create(&philo[tnum].thread_id, NULL, &thread_start, (void *)&philo[tnum]))
		{
			perror("pthread_create error!");
			ft_free_all(&g, &philo);
			return (-1);
		}
	}
	tnum = -1;
	while (++tnum < g.philo_nbr)
	{
		if (pthread_join(philo[tnum].thread_id, NULL))
		{
			perror("pthread_create error!");
			ft_free_all(&g, &philo);
			return (-1);
		}
	}
//	pthread_mutex_init(mutex, NULL);
	ft_free_all(&g, &philo);
	return (0);
}
//	pthread_detach();
//	pthread_mutex_init();
//	pthread_mutex_destroy();
//	pthread_mutex_lock();
//	pthread_mutex_unlock();
