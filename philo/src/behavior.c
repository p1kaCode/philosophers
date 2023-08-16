/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:58:28 by lmorel            #+#    #+#             */
/*   Updated: 2023/08/16 21:10:30 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_behavior(void *p_void)
{
	t_philo		*philo;

	philo = (t_philo *)p_void;
	pthread_mutex_lock(&philo->params->monitoring);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->params->monitoring);
	if (philo->params->number == 1)
		return (state_log(philo, THINK), state_log(philo, FORK), (void *)0);
	while (1)
	{
		state_log(philo, THINK);
		pthread_mutex_lock(&philo->params->monitoring);
		if (philo->params->end.__data.__lock == 1)
		{
			pthread_mutex_unlock(&philo->params->monitoring);
			break ;
		}
		pthread_mutex_unlock(&philo->params->monitoring);
		eat(philo);
		go_sleep(philo);
	}
	return ((void *)0);
}
