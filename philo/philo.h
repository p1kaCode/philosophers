/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:18:06 by lmorel            #+#    #+#             */
/*   Updated: 2023/03/12 00:05:21 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data{
	int	number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_numbers;
}		t_data;

# define SUCCESS 0
# define ERROR -1
# define MSG_ERROR_ARGS "Error\t: Invalid arguments.\n"

int	ft_atoi(char *str);
#endif