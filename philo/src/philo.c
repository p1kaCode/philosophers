/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:16:36 by lmorel            #+#    #+#             */
/*   Updated: 2023/03/16 01:44:38 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	arg_checking(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (ERROR);
	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) < 1 && i != 5)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	launch_threads(t_data *params)
{
	pthread_t	tid;
	int			i;
	t_philo		*philo;

	i = 0;
	while (i < params->number)
	{
		philo = &params->table[i];
		if (pthread_create(&tid, NULL, philo_behavior, philo) != 0)
			return (ERROR);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (SUCCESS);
}

void	*meals_detector(void *p_void)
{
	t_data	*params;
	int		i;

	params = (t_data *)p_void;
	i = 0;
	while (i < params->number)
	{
		pthread_mutex_lock(&params->table[i].mutex);
		if (params->table[i].meals >= params->meals_numbers)
			i++;
		pthread_mutex_unlock(&params->table[i].mutex);
		if (i == params->number)
		{
			end_log(params);
			pthread_mutex_unlock(&params->finished);
			return ((void *)0);
		}
		usleep(1000);
	}
	return ((void *)1);
}

int	main(int ac, char **av)
{
	t_data		params;
	pthread_t	tid;

	if (arg_checking(ac, av))
	{
		printf(MSG_ERROR_ARGS);
		return (ERROR);
	}
	if (initialization(&params, ac, av))
		return (ERROR);
	if (params.meals_numbers > 0)
	{
		if (pthread_create(&tid, NULL, meals_detector, &params) != 0)
			return (ERROR);
		pthread_detach(tid);
	}
	if (launch_threads(&params) == ERROR)
		return (ERROR);
	pthread_mutex_lock(&params.finished);
	pthread_mutex_unlock(&params.finished);
	return (SUCCESS);
}
