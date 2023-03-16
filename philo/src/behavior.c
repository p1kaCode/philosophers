/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:58:28 by lmorel            #+#    #+#             */
/*   Updated: 2023/03/16 01:30:34 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*life_checker(void *p_void)
{
	t_philo	*philo;

	philo = (t_philo *)p_void;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && get_time() > (philo->last_eat
				+ philo->params->time_to_die))
		{
			state_log(philo, "\x1B[31mis dead\x1B[0m");
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->params->finished);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(5000);
	}
}

void	*philo_behavior(void *p_void)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)p_void;
	philo->last_eat = get_time();
	if (pthread_create(&tid, NULL, &life_checker, p_void) != 0)
		return ((void *)1);
	pthread_detach(tid);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		go_sleep(philo);
		state_log(philo, "is thinking");
	}
	return ((void *)0);
}
