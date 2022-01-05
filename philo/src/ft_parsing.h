void	ft_get_args(char **av, t_env *g)
{
	if (av[1])
		g->philo_nbr = ft_atoi(av[1]);
	if (av[2])
		g->time_to_die = ft_atoi(av[2]);
	if (av[3])
		g->time_to_eat = ft_atoi(av[3]) * 1000;
	if (av[4])
		g->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		g->nb_max_meal = ft_atoi(av[5]);
	else
		g->nb_max_meal = INT_MAX;
}
