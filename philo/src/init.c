/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:58:08 by lmorel            #+#    #+#             */
/*   Updated: 2023/08/16 21:07:26 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_philos(t_data *params)
{
	int	i;

	i = 0;
	while (i < params->number)
	{
		params->table[i].id = i;
		params->table[i].params = params;
		params->table[i].meals = 0;
		params->table[i].is_eating = 0;
		i++;
	}
	init_forks(params);
	return (SUCCESS);
}

int	init_mutexes(t_data *params)
{
	int	i;

	pthread_mutex_init(&params->writing, NULL);
	params->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* params->number);
	if (!(params->forks))
		return (ERROR);
	i = 0;
	while (i < params->number)
	{
		pthread_mutex_init(&params->forks[i], NULL);
		i++;
	}
	return (init_philos(params));
}

int	initialization(t_data *params, int ac, char **av)
{
	params->number = ft_atoi(av[1]);
	params->time_to_die = ft_atoi(av[2]);
	params->time_to_eat = ft_atoi(av[3]);
	params->time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&params->monitoring, NULL);
	pthread_mutex_init(&params->end, NULL);
	params->all_dead = 0;
	if (ac == 6)
		params->meals_numbers = ft_atoi(av[5]);
	else
		params->meals_numbers = 0;
	params->table = (t_philo *)malloc(sizeof(t_philo) * params->number);
	if (!params->table)
		return (ERROR);
	params->start_time = get_time();
	return (init_mutexes(params));
}

int	free_data(t_data *params, int ret)
{
	int	i;

	i = 0;
	while (i < params->number)
	{
		pthread_mutex_destroy(&params->forks[i]);
		pthread_mutex_destroy(&params->table[i].mutex);
		i++;
	}
	free(params->forks);
	free(params->table);
	pthread_mutex_destroy(&params->writing);
	pthread_mutex_destroy(&params->monitoring);
	if (ret == SUCCESS)
		return (SUCCESS);
	else
		return (1);
}
