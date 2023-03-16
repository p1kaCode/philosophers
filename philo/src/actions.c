/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:40:17 by lmorel            #+#    #+#             */
/*   Updated: 2023/03/16 02:26:14 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo)
{
	int	nb;

	nb = philo->params->number;
	pthread_mutex_lock(&philo->params->forks[philo->id]);
	state_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->params->forks[(philo->id + 1) % nb]);
	state_log(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	state_log(philo, "\x1B[34mis eating\x1B[0m");
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
	state_log(philo, "is sleeping");
	usleep(philo->params->time_to_sleep * 1000);
}
