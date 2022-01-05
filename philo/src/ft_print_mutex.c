/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:38:43 by melperri          #+#    #+#             */
/*   Updated: 2022/01/05 20:23:55 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

static void	ft_write_action(char *time, char *id, int action, t_thread_info *philo)
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
	{
		philo->g->run = 1;
		write(1, STR_DIE, sizeof(STR_DIE));
	}
}

int	ft_print_mutex(t_env *g, t_thread_info *philo, int action)
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
	if (philo->g->run == 0)
		ft_write_action(time, id, action, philo);
	if (pthread_mutex_unlock(&g->print_mutex) == -1)
		return (-1);
	ft_free((void **)&id);;
	ft_free((void **)&time);;
	return (0);
}
