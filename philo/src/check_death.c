/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:43:12 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/23 14:43:18 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	check_death(t_philo *philo)
{
	bool	dead;

	if (pthread_mutex_lock(philo->dead_lock) != 0)
		return (ft_fprintf(STDERR_FILENO,
				"ERROR: locking dead mutex in philo %d", philo->id),
					true);
	dead = *philo->dead;
	if (pthread_mutex_unlock(philo->dead_lock) != 0)
		return (ft_fprintf(STDERR_FILENO,
				"ERROR: unlocking dead mutex in philo %d", philo->id),
					true);
	return (dead);
}
