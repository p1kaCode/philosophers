/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:05:33 by lmorel            #+#    #+#             */
/*   Updated: 2023/05/16 19:31:06 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	meals_detector(t_data *params)
{
	int		i;

	i = 0;
	while (i < params->number)
	{
		pthread_mutex_lock(&params->table[i].mutex);
		if (params->table[i].meals >= params->meals_numbers)
		{
			pthread_mutex_unlock(&params->table[i].mutex);
			i++;
		}
		else
			pthread_mutex_unlock(&params->table[i].mutex);
		if (i == params->number)
			return (0);
	}
	return (1);
}	

int	check_meals(t_data *params)
{
	if (params->meals_numbers > 0 && meals_detector(params) == 0)
	{
		pthread_mutex_lock(&params->writing);
		end_log(params);
		params->all_dead = 1;
		pthread_mutex_unlock(&params->writing);
		return (1);
	}
	return (0);
}

int	live_monitor(t_data *params)
{
	t_philo	philo;
	int		i;

	i = 0;
	while (i < params->number && params->all_dead == 0)
	{
		philo = params->table[i];
		if (!philo.is_eating && get_time() > \
		(philo.last_eat + params->time_to_die))
		{
			pthread_mutex_lock(&params->writing);
			state_log(&philo, "\x1B[31mis dead\x1B[0m");
			params->all_dead = 1;
			pthread_mutex_unlock(&params->writing);
			return (1);
		}
		i++;
	}
	return (0);
}

void	end_process(t_data *params)
{
	int	i;

	i = 0;
	while (i < params->number)
	{
		pthread_join(params->table[i].tid, NULL);
		i++;
	}
	return ;
}

int	wait_end(t_data *params)
{
	while (1)
	{
		usleep(5);
		if (live_monitor(params) == 1 || check_meals(params) == 1)
			break ;
	}
	end_process(params);
	return (SUCCESS);
}	
