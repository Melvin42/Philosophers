/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:16:53 by melperri          #+#    #+#             */
/*   Updated: 2022/01/05 18:20:19 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_write_action(char *time, char *id, int action)
{
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	write(1, id, ft_strlen(id));
	if (action == FORK)
		write(1, STR_FORK, sizeof(STR_FORK));
	else if (action == EAT)
		write(1, STR_EAT, sizeof(STR_EAT));
	else if (action == SLEEP)
		write(1, STR_SLEEP, sizeof(STR_SLEEP));
	else if (action == THINK)
		write(1, STR_THINK, sizeof(STR_THINK));
	else if (action == DIE)
		write(1, STR_DIE, sizeof(STR_DIE));
}

static int	ft_print_mutex(t_env *g, t_thread_info *philo, int action)
{
	char	*time;
	char	*id;

	time = ft_itoa((int)philo->time_to_ret);
	if (time == NULL)
		return (-1);
	id = ft_itoa(philo->philo_id);
	if (id == NULL)
	{
		ft_free((void **)&time);
		return (-1);
	}
	if (pthread_mutex_lock(&g->print_mutex) == -1)
		return (-1);
	ft_write_action(time, id, action);
	if (pthread_mutex_unlock(&g->print_mutex) == -1)
		return (-1);
	ft_free((void **)&id);;
	ft_free((void **)&time);;
	return (0);
}

void	ft_take_forks(t_thread_info *philo, int fork_id)
{
	if (pthread_mutex_lock(&philo->g->forks[fork_id].mutex) == -1)
	{
		perror("Mutex lock failed");
		exit(1);
	}
	get_real_time(philo->g->tv, philo);
	philo->is_thinking = 1;
	if (ft_print_mutex(philo->g, philo, FORK))
		return ;
//	printf("%ld %d %s %d\n", philo->time_to_ret, philo->philo_id , STR_FORK, fork_id + 1);
}

void	ft_think(t_thread_info *philo)
{
	get_real_time(philo->g->tv, philo);
	ft_print_mutex(philo->g, philo, THINK);
}

void	ft_sleep(t_thread_info *philo)
{
	get_real_time(philo->g->tv, philo);
	ft_print_mutex(philo->g, philo, SLEEP);
	usleep(philo->g->time_to_sleep * 1000);
	if (philo->philo_id == 1)
	{
		pthread_mutex_unlock(&(philo->g->forks[philo->g->philo_nbr - 1]).mutex);
		pthread_mutex_unlock(&(philo->g->forks[0]).mutex);
	}
	else if (philo->philo_id > 1)
	{
		pthread_mutex_unlock(&(philo->g->forks[philo->philo_id - 2]).mutex);
		pthread_mutex_unlock(&(philo->g->forks[philo->philo_id - 1]).mutex);
	}
}

void	ft_eat(t_thread_info *philo)
{
	get_real_time(philo->g->tv, philo);
	ft_print_mutex(philo->g, philo, EAT);
	philo->last_meal = philo->time_to_ret;
	philo->nb_meal_ate++;
	usleep(philo->g->time_to_eat * 1000);
	ft_sleep(philo);
}

int	ft_can_philo_take_forks(t_thread_info *philo, int status)
{
	if (status == ODD)
	{
		if (philo->philo_id == 1)
		{
			ft_take_forks(philo, philo->g->philo_nbr - 1);
			ft_take_forks(philo, 0);
			return (1);
		}
		else if (philo->philo_id > 1)
		{
			ft_take_forks(philo, philo->philo_id - 2);
			ft_take_forks(philo, philo->philo_id - 1);
			return (1);
		}
	}
	else
	{
		usleep(20);
		ft_take_forks(philo, philo->philo_id - 1);
		ft_take_forks(philo, philo->philo_id - 2);
		return (1);
	}
	return (0);
}

int	ft_is_philo_even(t_thread_info *philo)
{
	if ((philo->philo_id - 1) % 2 == 0)
	{
		return (ft_can_philo_take_forks(philo, ODD));
	}
	else
	{
		usleep(20);
		return (ft_can_philo_take_forks(philo, EVEN));
	}
	return (0);
}
