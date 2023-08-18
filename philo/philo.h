/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:18:06 by lmorel            #+#    #+#             */
/*   Updated: 2023/08/18 02:05:34 by lmorel           ###   ########.fr       */
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
	pthread_t		tid;
	struct s_data	*params;
	int				meals;
	int				is_eating;
	__uint64_t		last_eat;
	int				own_fork;
	int				*right_fork;
	pthread_mutex_t	*m_ofork;
	pthread_mutex_t	*m_rfork;
}	t_philo;

typedef struct s_data{
	int				number;
	__uint64_t		time_to_die;
	__uint64_t		time_to_eat;
	__uint64_t		time_to_sleep;
	int				meals_numbers;
	int				all_dead;
	__uint64_t		start_time;
	t_philo			*table;
	pthread_mutex_t	*forks;
	pthread_mutex_t	monitoring;
	pthread_mutex_t	end;
	pthread_mutex_t	writing;
}		t_data;

# define SUCCESS 0
# define ERROR -1
# define MSG_ERROR_ARGS "\x1B[31mError\x1B[0m\t: Invalid arguments.\n"
# define MSG_END "👍 All the philosophers have eaten enought. 👍"
# define MSG_FORMAT "\x1B[31mInvalid use\x1B[0m\t: ./philo [Nb of philos] \
[Time to die] [Time to eat] [Time to sleep] (Optionnal \
:[Nb of meals])\n\x1B[32mPlease retry.\x1B[0m\n"

# define FORK "has taken a fork"
# define EAT "\x1B[34mis eating\x1B[0m"
# define SLEEP "is sleeping"
# define THINK "is thinking"

__uint64_t	get_time(void);
int			ft_atoi(const char *str);
int			initialization(t_data *params, int ac, char **av);
void		*philo_behavior(void *p_void);
int			take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		go_sleep(t_philo *philo);
void		state_log(t_philo *philo, char *msg);
void		end_log(t_data *params);
int			wait_end(t_data *params);
int			free_data(t_data *params, int ret);
int			init_philos(t_data *params);
void		let_forks(t_philo *philo);
void		init_forks(t_data *params);
#endif