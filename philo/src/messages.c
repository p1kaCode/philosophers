/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 01:44:16 by lmorel            #+#    #+#             */
/*   Updated: 2023/03/16 01:44:47 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	state_log(t_philo *philo, char *msg)
{
	__uint64_t	elapsed;

	elapsed = get_time() - philo->params->start_time;
	pthread_mutex_lock(&philo->params->writing);
	printf("%ld\t: %d %s\n", elapsed, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->params->writing);
}

void	end_log(t_data *params)
{
	__uint64_t	elapsed;

	elapsed = get_time() - params->start_time;
	pthread_mutex_lock(&params->writing);
	printf("%ld\t: \x1B[32m%s\n\x1B[0m", elapsed, MSG_END);
	pthread_mutex_unlock(&params->writing);
}
