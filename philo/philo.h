/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:18:06 by lmorel            #+#    #+#             */
/*   Updated: 2023/03/21 19:56:19 by lmorel           ###   ########.fr       */
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

struct	s_data;

typedef struct s_philo{
	int				id;
	struct s_data	*params;
	int				meals;
	int				is_eating;
	__uint64_t		last_eat;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_data{
	int				number;
	__uint64_t		time_to_die;
	__uint64_t		time_to_eat;
	__uint64_t		time_to_sleep;
	int				meals_numbers;
	__uint64_t		start_time;
	t_philo			*table;
	pthread_mutex_t	*forks;
	pthread_mutex_t	finished;
	pthread_mutex_t	writing;
}		t_data;

# define SUCCESS 0
# define ERROR -1
# define MSG_ERROR_ARGS "Error\t: Invalid arguments.\n"
# define MSG_END "All the philosophers have eaten enought"

__uint64_t	get_time(void);
int			ft_atoi(const char *str);
int			initialization(t_data *params, int ac, char **av);
void		*philo_behavior(void *p_void);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		go_sleep(t_philo *philo);
void		state_log(t_philo *philo, char *msg);
void		end_log(t_data *params);
int			free_data(t_data *params, int ret);
#endif