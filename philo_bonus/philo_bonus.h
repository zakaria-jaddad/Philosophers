/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:05:27 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/27 23:02:17 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "fprintf/ft_fprintf.h"
#include <signal.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/wait.h>
#include <string.h>

# define MAX_PHILOS 200

typedef struct s_philo
{
	pid_t	pid;
	int		id;
	bool	is_sleeping;
	size_t	meals_eaten;
	size_t	num_times_to_eat;
	ssize_t	last_meal_time;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	start_time;

	sem_t   *dead_lock;
	bool	dead;

	sem_t	*print_lock;
	sem_t	*forks;

	// each philo share their 'is_eating' and 'done_eating'
	// variables with the observer
	bool	is_eating;
	sem_t	*is_eating_lock;
        char    *is_eating_sem_name;

	bool	done_eating;
	sem_t	*done_eating_lock;
        char    *done_eating_sem_name;
}			t_philo;

typedef struct s_info
{
	bool	death_flag;
	sem_t	*dead_lock;
	sem_t	*print_lock;
	sem_t	*forks;
	ssize_t	num_of_philos;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	num_times_to_eat;
	t_philo	philos[MAX_PHILOS];
}			t_info;

bool		isvalid_number(char *element);
ssize_t		ft_atoi(const char *str);
char		*ft_itoa(int n);
char		*ft_strcpy(char *s1, char *s2);
void		ft_strcat(char *des, const char *src);

#endif
