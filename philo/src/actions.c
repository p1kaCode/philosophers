/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:40:17 by lmorel            #+#    #+#             */
/*   Updated: 2023/05/25 15:27:42 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo)
{
	int	nb;

	if (philo->params->all_dead == 1)
		return ((void)0);
	nb = philo->params->number;
	pthread_mutex_lock(&philo->params->forks[philo->id]);
	if (philo->params->all_dead == 1)
		return ((void)0);
	pthread_mutex_lock(&philo->params->writing);
	state_log(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->params->writing);
	if (philo->params->all_dead == 1 || philo->params->number == 1)
		return ((void)0);
	pthread_mutex_lock(&philo->params->forks[(philo->id + 1) % nb]);
	if (philo->params->all_dead == 1)
		return ((void)0);
	pthread_mutex_lock(&philo->params->writing);
	state_log(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->params->writing);
}

void	eat(t_philo *philo)
{
	if (philo->params->all_dead == 1)
		return ((void)0);
	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	if (philo->params->all_dead == 1)
		return ((void)0);
	pthread_mutex_lock(&philo->params->writing);
	state_log(philo, "\x1B[34mis eating\x1B[0m");
	pthread_mutex_unlock(&philo->params->writing);
	usleep(philo->params->time_to_eat * 1000);
	philo->meals++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex);
}

void	go_sleep(t_philo *philo)
{
	int	nb;

	nb = philo->params->number;
	pthread_mutex_unlock(&philo->params->forks[philo->id]);
	pthread_mutex_unlock(&philo->params->forks[(philo->id + 1) % nb]);
	if (philo->params->all_dead == 1)
		return ((void)0);
	pthread_mutex_lock(&philo->params->writing);
	state_log(philo, "is sleeping");
	pthread_mutex_unlock(&philo->params->writing);
	usleep(philo->params->time_to_sleep * 1000);
}
