/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:40:17 by lmorel            #+#    #+#             */
/*   Updated: 2023/08/18 02:07:33 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait(unsigned long long time_ms)
{
	unsigned long long	time;

	time = get_time();
	usleep(time_ms * 900);
	while (get_time() - time < time_ms)
		usleep(100);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->params->monitoring);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->meals++;
	state_log(philo, EAT);
	pthread_mutex_unlock(&philo->params->monitoring);
	wait(philo->params->time_to_eat);
	pthread_mutex_lock(&philo->params->monitoring);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->params->monitoring);
	let_forks(philo);
}

void	go_sleep(t_philo *philo)
{
	state_log(philo, SLEEP);
	wait(philo->params->time_to_sleep);
}
