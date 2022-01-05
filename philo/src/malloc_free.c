/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:11:35 by melperri          #+#    #+#             */
/*   Updated: 2022/01/05 19:35:03 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_free(void **tofree)
{
	if (*tofree)
	{
		free(*tofree);
		*tofree = NULL;
	}
}

int	ft_free_all(t_thread_info **philo)
{
	int	i;

	i = -1;
	while (++i < (*philo)->g->philo_nbr)
	{
		if (pthread_mutex_destroy(&((*philo)->g->forks[i]).mutex) == -1)
		{
			perror("Mutex destroy failed");
			exit(0);
		}
	}
	ft_free((void **)philo);
	return (-1);
}

int	ft_malloc_simple(void **var, size_t n, int size)
{
	*var = malloc(n * size);
	if (!*var)
		return (-1);
	memset(*var, 0, n);
	return (0);
}
