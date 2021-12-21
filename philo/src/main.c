/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:16:58 by melperri          #+#    #+#             */
/*   Updated: 2021/12/21 19:19:29 by melperri         ###   ########.fr       */
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

static void	get_real_time(struct timeval tv_start, t_thread_info *philo)
{
	u_int64_t	sec;
	u_int64_t	usec;

	if (gettimeofday(&philo->tv, NULL) < 0)
		perror("gettimeofday failed");
	sec = (philo->tv.tv_sec - tv_start.tv_sec) * 1000000;
	usec = (philo->tv.tv_usec - tv_start.tv_usec);
	philo->g->time_to_ret = (sec + usec) / 1000;
}

static void	ft_take_forks(t_thread_info *philo, int fork_id)
{
	get_real_time(philo->g->tv, philo);
	philo->is_thinking = 1;
	(*philo->forks)[fork_id].available = NO;
	printf("%ld %d %s\n", philo->g->time_to_ret, philo->philo_id , FORK);
}

static void	ft_think(t_thread_info *philo)
{
	get_real_time(philo->g->tv, philo);
	printf("%ld %d %s\n", philo->g->time_to_ret, philo->philo_id , THINK);
}
static void	ft_sleep(t_thread_info *philo)
{
	get_real_time(philo->g->tv, philo);
	printf("%ld %d %s\n", philo->g->time_to_ret, philo->philo_id , SLEEP);
	usleep(philo->g->time_to_sleep * 1000);
}

static void	ft_eat(t_thread_info *philo)
{
	get_real_time(philo->g->tv, philo);
	printf("%ld %d %s\n", philo->g->time_to_ret, philo->philo_id , EAT);
	philo->last_meal = philo->g->time_to_ret;
	usleep(philo->g->time_to_eat * 1000);
	if (philo->philo_id == 1)
	{
		(*philo->forks)[philo->g->philo_nbr - 1].available = YES;
		(*philo->forks)[0].available = YES;
	}
	else if (philo->philo_id > 1)
	{
		(*philo->forks)[philo->philo_id - 1].available = YES;
		(*philo->forks)[philo->philo_id - 2].available = YES;
	}
	ft_sleep(philo);
}

static int	ft_can_philo_take_forks(t_thread_info *philo)
{
	if (philo->philo_id == 1)
	{
		if ((*philo->forks)[philo->g->philo_nbr - 1].available == NO
			|| (*philo->forks)[0].available == NO)
			return (0);
		ft_take_forks(philo, philo->g->philo_nbr - 1);
		ft_take_forks(philo, 0);
		return (1);
	}
	else if (philo->philo_id > 1)
	{
		if ((*philo->forks)[philo->philo_id - 1].available == NO
			|| (*philo->forks)[philo->philo_id - 2].available == NO)
			return (0);
		ft_take_forks(philo, philo->philo_id - 1);
		ft_take_forks(philo, philo->philo_id - 2);
		return (1);
	}
	return (0);
}

static void	*thread_start(void *thread)
{
	t_thread_info	*philo;

	philo = (t_thread_info *)thread;
	while (1)
	{
		get_real_time(philo->g->tv, philo);
//		printf("%d\n", ((int)philo->g->time_to_ret) - philo->last_meal);
		if ((int)philo->g->time_to_ret - philo->last_meal > philo->g->time_to_die)
		{
			printf("%ld %d %s\n", philo->g->time_to_ret, philo->philo_id , DIE);;
			exit(0);
		}
		if (ft_can_philo_take_forks(philo))
			ft_eat(philo);
		else if (philo->is_thinking == 0)
		{
			ft_think(philo);
			philo->is_thinking = 1;
		}
		usleep(5000);
	}
	return (philo);
}

static int	ft_create_forks_tab(t_thread_info **philo, t_env *g)
{
	int	i;

	i = -1;
	if (ft_malloc_simple((void **)&g->forks, sizeof(*g->forks), g->philo_nbr))
		return (-1);
	while (++i < g->philo_nbr)
	{
		g->forks[i].id = i + 1;
		g->forks[i].available = YES;
		(*philo)[i].forks = &g->forks;
	}
	return (0);
}

static int	ft_create_thread(t_thread_info **philo, t_env *g)
{
	int	tnum;

	if (ft_malloc_simple((void **)philo, sizeof(**philo), g->philo_nbr))
		return (-1);
	tnum = -1;
	if (ft_create_forks_tab(philo, g) == -1)
		return (-1);
	if (gettimeofday(&g->tv, NULL) < 0)
	{
		perror("gettimeofday failed");
		return (-1);
	}
	while (++tnum < g->philo_nbr)
	{
		usleep(20);
		(*philo)[tnum].philo_id = tnum + 1;
		(*philo)[tnum].g = g;
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

	philo = NULL;
	if (ac < 5 || ac > 6)
		return (write(1, ARG_ERROR, sizeof(ARG_ERROR)));
	ft_get_args(av, &g);
	if (ft_create_thread(&philo, &g))
		return (-1);
	ft_free_all(&philo);
	return (0);
}
