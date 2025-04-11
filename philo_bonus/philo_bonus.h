/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:05:27 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/10 18:23:28 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
#include <sys/types.h>
# include <unistd.h>

# define MAX_PHILOS 200

typedef struct s_philo
{
	pid_t		pid;
	int				id;
	bool			is_eating;
	bool			is_sleeping;
	bool			*dead;
	bool			done_eating;
	size_t			meals_eaten;
	size_t			num_times_to_eat;
	ssize_t			last_meal_time;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			start_time;

        // TODO: change mutex to ...
        // add pointer to forks
        // each time philo want a fork check if available forks to get from the array
	void	*r_fork;
	void	*l_fork;
	void	*print_lock;
	void	*dead_lock;
	int	meal_lock;
}					t_philo;

typedef struct s_info
{
	bool			death_flag;
        //
	int	dead_lock;
	int	print_lock;
	int	forks[MAX_PHILOS];
        //
	ssize_t			num_of_philos;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			num_times_to_eat;
	t_philo			philos[MAX_PHILOS];
}					t_info;

bool				isvalid_number(char *element);
ssize_t				ft_atoi(const char *str);

#endif
