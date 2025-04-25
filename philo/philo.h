/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:53:39 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/25 16:17:15 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./fprintf/ft_fprintf.h"
# include "fprintf/ft_fprintf.h"
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define MAX_PHILOS 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	bool			*dead;
	bool			done_eating;
	size_t			meals_eaten;
	size_t			num_times_to_eat;
	ssize_t			last_meal_time;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	eating;
	pthread_mutex_t	done_eating_lock;
}					t_philo;

typedef struct s_info
{
	bool			death_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	forks[MAX_PHILOS];
	ssize_t			num_of_philos;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			num_times_to_eat;
	t_philo			philos[MAX_PHILOS];
}					t_info;

// input parse
bool				isvalid_number(char *element);
bool				isvalid_args(int argc, char **argv);

//
int					ft_atoi(const char *str);

// time utils
ssize_t				get_current_time(void);
ssize_t				get_current_timestamp(ssize_t start_time);
int					ft_usleep(size_t ms);

// print utils
void				print_usage(void);
void				safe_print(char *s, t_philo *philo);
int					print_error(char *err);

bool				check_death(t_philo *philo);

// init information
bool				init_info(t_info *info, char **data);
bool				init_philo(t_info *info, t_philo *philo, size_t id);
bool				init_philos(t_info *info);
bool				init_forks(t_info *info);

// philo actions
void				philo_think(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_eat(t_philo *philo);

// philo utils
void				*philo_routine(void *data);
bool				philo_done_eating(t_philo *philo);
bool				philos_done_eating(t_philo *philos, size_t num_of_philos);
bool				start_philos(t_info *info);

// observer
void				*observe(void *data);

bool				clean(t_info *info);
#endif
