/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:16:36 by lmorel            #+#    #+#             */
/*   Updated: 2023/05/16 19:19:15 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	arg_checking(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		printf(MSG_FORMAT);
		return (ERROR);
	}
	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) < 1 || ft_atoi(av[1]) > 200)
		{
			printf(MSG_ERROR_ARGS);
			return (ERROR);
		}
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
		philo = (void *)&params->table[i];
		if (pthread_create(&tid, NULL, philo_behavior, philo) != 0)
			return (ERROR);
		params->table[i].tid = tid;
		usleep(200);
		i++;
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_data		params;

	if (arg_checking(ac, av))
		return (ERROR);
	if (initialization(&params, ac, av))
		return (free_data(&params, ERROR));
	if (launch_threads(&params) == ERROR)
		return (free_data(&params, ERROR));
	wait_end(&params);
	return (free_data(&params, SUCCESS));
}
