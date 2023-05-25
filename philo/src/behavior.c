/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:58:28 by lmorel            #+#    #+#             */
/*   Updated: 2023/05/25 15:43:31 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_behavior(void *p_void)
{
	t_philo		*philo;

	philo = (t_philo *)p_void;
	philo->last_eat = get_time();
	while (philo->params->all_dead == 0)
	{
		take_forks(philo);
		if (philo->params->number == 1)
			return ((void *)0);
		eat(philo);
		go_sleep(philo);
		if (philo->params->all_dead == 1)
			return ((void *)0);
		pthread_mutex_lock(&philo->params->writing);
		state_log(philo, "is thinking\t🤔");
		pthread_mutex_unlock(&philo->params->writing);
	}
	return ((void *)0);
}
