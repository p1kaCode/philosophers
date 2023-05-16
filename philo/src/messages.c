/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 01:44:16 by lmorel            #+#    #+#             */
/*   Updated: 2023/05/16 19:08:56 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	state_log(t_philo *philo, char *msg)
{
	__uint64_t	elapsed;

	if (philo->params->all_dead == 1)
		return ((void)0);
	elapsed = get_time() - philo->params->start_time;
	printf("%ld\t: %d %s\n", elapsed, philo->id + 1, msg);
}

void	end_log(t_data *params)
{
	__uint64_t	elapsed;

	elapsed = get_time() - params->start_time;
	printf("%ld\t: \x1B[32m%s\n\x1B[0m", elapsed, MSG_END);
}
