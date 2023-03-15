/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:16:36 by lmorel            #+#    #+#             */
/*   Updated: 2023/03/16 00:31:42 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	arg_checking(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (ERROR);
	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) < 1)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

void	print_log(t_philo *philo, char *msg)
{
	__uint64_t	elapsed;

	elapsed = get_time() - philo->params->start_time;
	printf("%ld\t: %d %s\n", elapsed, philo->id + 1, msg);
}

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
			print_log(philo, "\x1B[31mis dead\x1B[0m");
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
		print_log(philo, "is thinking");
	}
	return ((void *)0);

}

int	main(int ac, char **av)
{
	t_data		params;
	pthread_t	tid;
	int			i;
	t_philo		*philo;

	if (arg_checking(ac, av))
	{
		printf(MSG_ERROR_ARGS);
		return (ERROR);
	}
	initialization(&params, ac, av);
	i = 0;
	while (i < params.number)
	{
		philo = &params.table[i];
		if (pthread_create(&tid, NULL, philo_behavior, philo) != 0)
			return (ERROR);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	pthread_mutex_lock(&params.finished);
	pthread_mutex_unlock(&params.finished);
	return (SUCCESS);
}
