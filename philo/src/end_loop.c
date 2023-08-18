/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:05:33 by lmorel            #+#    #+#             */
/*   Updated: 2023/08/18 02:02:07 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	meals_detector(t_data *params)
{
	int		i;

	i = 0;
	while (i < params->number)
	{
		if (params->table[i].meals >= params->meals_numbers)
			i++;
		else
			break ;
		if (i == params->number)
			return (0);
	}
	return (1);
}

int	check_meals(t_data *params)
{
	if (params->all_dead == 1)
		return (1);
	if (params->meals_numbers > 0 && meals_detector(params) == 0)
	{
		end_log(params);
		pthread_mutex_lock(&params->end);
		params->all_dead = 1;
		return (1);
	}
	return (0);
}

int	live_monitor(t_data *params)
{
	t_philo	*philo;
	int		i;

	i = 0;
	if (params->all_dead)
		return (1);
	while (i < params->number && params->all_dead == 0)
	{
		philo = &params->table[i];
		if (!philo->is_eating && \
			(get_time() - philo->last_eat >= params->time_to_die))
		{
			state_log(philo, "\x1B[31mdied\x1B[0m");
			pthread_mutex_lock(&philo->params->end);
			params->all_dead = 1;
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
		pthread_mutex_lock(&params->monitoring);
		if (live_monitor(params) == 1 || check_meals(params) == 1)
		{
			pthread_mutex_unlock(&params->monitoring);
			break ;
		}
		pthread_mutex_unlock(&params->monitoring);
		usleep(1000);
	}
	end_process(params);
	pthread_mutex_unlock(&params->end);
	return (SUCCESS);
}
