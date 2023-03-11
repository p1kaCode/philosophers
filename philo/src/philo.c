/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:16:36 by lmorel            #+#    #+#             */
/*   Updated: 2023/03/12 00:13:21 by lmorel           ###   ########.fr       */
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
		if (ft_atoi(av[i]) < 1)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

void	initialization(t_data *params, int ac, char **av)
{
	params->number = ft_atoi(av[1]);
	params->time_to_die = ft_atoi(av[2]);
	params->time_to_eat = ft_atoi(av[3]);
	params->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		params->meals_numbers = ft_atoi(av[5]);
	else
		params->meals_numbers = -1;
}

int	main(int ac, char **av)
{
	t_data	params;

	if (arg_checking(ac, av))
	{
		printf(MSG_ERROR_ARGS);
		return (ERROR);
	}
	initialization(&params, ac, av);
	return (SUCCESS);
}
