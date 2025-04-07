/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:53:39 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/07 20:00:22 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOS 200

typedef int			t_bool;
enum				e_bool
{
	True = 1,
	False = 0,
};

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	t_bool			is_eating;
	t_bool			is_sleeping;
	t_bool			*dead;
	size_t			meals_eaten;
	size_t			num_times_to_eat;
	t_bool			done_eating;
	ssize_t			last_meal_time;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	meal_lock;
}					t_philo;

typedef struct s_info
{
	t_bool			death_flag;
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

t_bool				isvalid_number(char *element);
ssize_t				ft_atoi(const char *str);

#endif
