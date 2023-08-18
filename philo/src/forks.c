/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:40:48 by lmorel            #+#    #+#             */
/*   Updated: 2023/08/18 02:07:19 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	let_forks(t_philo *philo)
{
	if (philo->params->number > 1)
	{
		pthread_mutex_lock(philo->m_rfork);
		*philo->right_fork = 1;
		pthread_mutex_unlock(philo->m_rfork);
		pthread_mutex_lock(philo->m_ofork);
		philo->own_fork = 1;
		pthread_mutex_unlock(philo->m_ofork);
	}
	else
	{
		pthread_mutex_lock(philo->m_ofork);
		philo->own_fork = 1;
		pthread_mutex_unlock(philo->m_ofork);
	}
}

int	lock_second_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->m_rfork);
		if (*philo->right_fork == 1)
		{
			state_log(philo, "has taken a fork");
			*philo->right_fork = 0;
			pthread_mutex_unlock(philo->m_rfork);
			break ;
		}
		pthread_mutex_unlock(philo->m_rfork);
		usleep(1000);
	}
	return (1);
}

int	take_forks(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->m_ofork);
		if (philo->own_fork == 1)
		{
			state_log(philo, "has taken a fork");
			philo->own_fork = 0;
			pthread_mutex_unlock(philo->m_ofork);
			if (philo->params->number > 1)
			{
				if (!lock_second_fork(philo))
					return (0);
				else
					break ;
			}
			else
				return (1);
		}
		pthread_mutex_unlock(philo->m_ofork);
		usleep(1000);
	}
	return (1);
}

void	init_forks(t_data *params)
{
	int	i;

	i = params->number - 1;
	if (params->number == 1)
	{
		params->table[0].m_ofork = &params->forks[i];
		params->table[0].own_fork = 1;
		return ;
	}
	params->table[i].m_ofork = &params->forks[i];
	params->table[i].own_fork = 1;
	while (i-- > 0)
	{
		params->table[i].m_ofork = &params->forks[i];
		params->table[i].m_rfork = &params->forks[i + 1];
		params->table[i].own_fork = 1;
		params->table[i].right_fork = &params->table[i + 1].own_fork;
	}
	params->table[params->number - 1].m_rfork = &params->forks[0];
	params->table[params->number - 1].right_fork = \
		&params->table[0].own_fork;
}
