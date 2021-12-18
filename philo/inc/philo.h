/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:17:55 by melperri          #+#    #+#             */
/*   Updated: 2021/12/18 17:33:17 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

# define ARG_ERROR "Bad numbers of argument.\n"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct	s_forks {
	int	id;
} t_forks;

typedef struct	s_thread_info {
	struct timeval	tv;
	pthread_t		thread_id;
	int				thread_num;
	t_forks			**forks;
	char			*argv_string;
} t_thread_info;

typedef struct	s_env
{
	int		philo_nbr;
	int		*philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_of_each_philo_must_eat;
	t_forks	*forks;
}	t_env;

int	ft_atoi(const char *nptr);

#endif
