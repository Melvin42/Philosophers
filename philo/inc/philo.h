/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:17:55 by melperri          #+#    #+#             */
/*   Updated: 2022/01/08 16:56:30 by melperri         ###   ########.fr       */
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

# define ARG_ERROR "Bad arguments.\n"
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
	DIE,
	STOP
};

enum e_status {
	ODD,
	EVEN
};

typedef struct	s_forks {
	pthread_mutex_t	mutex;
} t_forks;

typedef struct	s_thread_info t_thread_info;

typedef struct	s_env
{
	t_thread_info	*philo;
	t_forks			*forks;
	struct timeval	tv;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	monitor_mutex;
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_max_meal;
	bool			run;
}	t_env;

typedef	struct	s_thread_info
{
	t_env			*g;
	struct timeval	tv;
	pthread_t		thread_id;
	u_int64_t		time_to_ret;
	int				philo_id;
	int				last_meal;
	int				nb_meal_ate;
	char			*argv_string;
	bool			alive;
} t_thread_info;

/*	main.c */
void	get_real_time(struct timeval tv_start, t_thread_info *philo);
void	*thread_start(void *thread);

/*	ft_parsing.c */
int		ft_zero(char *s);
void	ft_get_args(char **av, t_env *g);
int		ft_check_args(int ac, char **av);

/*	ft_init.c */
int		ft_create_thread(t_thread_info **philo, t_env *g);
int		ft_program(t_thread_info **philo, t_env *g);

/*	philo_actions.c */
void	ft_lock_first_forks(t_thread_info *philo, int fork_id, int status);
void	ft_lock_second_forks(t_thread_info *philo, int fork_id);
void	ft_sleep(t_thread_info *philo);
void	ft_eat(t_thread_info *philo);
void	ft_can_philo_lock_forks(t_thread_info *philo, int status);
int		ft_is_philo_even(int philo_id);

/*	ft_die.c */
void	ft_is_one_philo_dead(t_thread_info *philo);
void	ft_is_philo_alive(t_thread_info *philo, int status);

/*	ft_print_mutex.c */
void	ft_print_mutex(t_env *g, t_thread_info *philo, int action);

/*	malloc_free.c */
void	ft_free(void **tofree);
int		ft_free_all(t_thread_info **philo);
int		ft_malloc_simple(void **var, size_t n, int size);

/*	utils */
int		ft_strlen(char *s);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

#endif
