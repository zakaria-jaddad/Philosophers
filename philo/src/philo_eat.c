/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:40:13 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/26 02:29:08 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

static bool	lock_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (ft_fprintf(STDERR_FILENO, "ERROR: locking right "
				"fork mutex in philo %d", philo->id), false);
	safe_print("%zu %d has taken a fork\n", philo);
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (ft_fprintf(STDERR_FILENO, "ERROR: locking left "
				"fork mutex in philo %d", philo->id), false);
	safe_print("%zu %d has taken a fork\n", philo);
	return (true);
}

static bool	unlock_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return (ft_fprintf(STDERR_FILENO, "ERROR: unlocking right "
				"fork mutex in philo %d", philo->id), false);
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return (ft_fprintf(STDERR_FILENO, "ERROR: unlocking left "
				"fork mutex in philo %d", philo->id), false);
	return (true);
}

void	philo_eat(t_philo *philo)
{
	ssize_t	last_meal_time;

	if (lock_forks(philo) == false)
		return ;
	safe_print("%zu %d is eating\n", philo);
	pthread_mutex_lock(&philo->eating);
	last_meal_time = get_current_time();
	if (last_meal_time == -1)
		return ((void)ft_fprintf(STDERR_FILENO, "ERROR: gettimeofday\n"));
	philo->last_meal_time = last_meal_time;
	philo->meals_eaten++;
	if (pthread_mutex_unlock(&philo->eating) != 0)
		return ((void) ft_fprintf(STDERR_FILENO, "ERROR: locking eating "
				"mutex in philo %d", philo->id));
	ft_usleep(philo->time_to_eat);
	if (unlock_forks(philo) == false)
		return ;
}
