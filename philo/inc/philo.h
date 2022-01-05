/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:17:55 by melperri          #+#    #+#             */
/*   Updated: 2022/01/05 18:06:36 by melperri         ###   ########.fr       */
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
# include <stdbool.h>
# include <stddef.h>

# define ARG_ERROR "Bad numbers of argument.\n"
# define STR_FORK " has taken a fork\n"
# define STR_EAT " is eating\n"
# define STR_SLEEP " is sleeping\n"
# define STR_THINK " is thinking\n"
# define STR_DIE " died\n"

enum e_action{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

enum e_status {
	ODD,
	EVEN
};

typedef struct	s_forks {
	pthread_mutex_t	mutex;
} t_forks;

typedef struct	s_env
{
	pthread_mutex_t	print_mutex;
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_max_meal;
	struct timeval	tv;
	t_forks			*forks;
}	t_env;

typedef struct	s_thread_info {
	struct timeval	tv;
	pthread_t		thread_id;
	t_env			*g;
	u_int64_t		time_to_ret;
	int				philo_id;
	int				last_meal;
	int				nb_meal_ate;
	char			*argv_string;
	bool			is_thinking;
} t_thread_info;

int		ft_strlen(char *s);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

/*	malloc_free.c */
void	ft_free(void **tofree);
int		ft_free_all(t_thread_info **philo);
int		ft_malloc_simple(void **var, size_t n, int size);

/*	philo_actions.c */
void	ft_take_forks(t_thread_info *philo, int fork_id);
void	ft_think(t_thread_info *philo);
void	ft_sleep(t_thread_info *philo);
void	ft_eat(t_thread_info *philo);
int		ft_can_philo_take_forks(t_thread_info *philo, int status);
int		ft_is_philo_even(t_thread_info *philo);

void	get_real_time(struct timeval tv_start, t_thread_info *philo);

#endif
