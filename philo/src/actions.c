/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:40:17 by lmorel            #+#    #+#             */
/*   Updated: 2023/08/15 23:54:12 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork);
		state_log(philo, FORK);
		pthread_mutex_lock(philo->rfork);
		state_log(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		state_log(philo, FORK);
		pthread_mutex_lock(philo->lfork);
		state_log(philo, FORK);
	}
}

void	let_forks(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
	{
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
	}
	else
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->params->monitoring);
	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->meals++;
	state_log(philo, EAT);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->params->monitoring);
	usleep(philo->params->time_to_eat * 1000);
	pthread_mutex_lock(&philo->params->monitoring);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->params->monitoring);
	let_forks(philo);
}

void	go_sleep(t_philo *philo)
{
	state_log(philo, SLEEP);
	usleep(philo->params->time_to_sleep * 1000);
}
