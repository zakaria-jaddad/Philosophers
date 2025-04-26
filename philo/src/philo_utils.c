/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:18:03 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/25 22:59:18 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	philo_done_eating(t_philo *philo)
{
	bool	done_eating;

	if (pthread_mutex_lock(&philo->done_eating_lock) != 0)
		return (ft_fprintf(STDERR_FILENO,
				"ERROR: locking done eating mutex in philo %d\n", philo->id),
			true);
	done_eating = philo->done_eating;
	if (pthread_mutex_unlock(&philo->done_eating_lock) != 0)
		return (ft_fprintf(STDERR_FILENO,
				"ERROR: unlocking done eating mutex in philo %d\n", philo->id),
			true);
	return (done_eating);
}

bool	philos_done_eating(t_philo *philos, size_t num_of_philos)
{
	size_t	i;

	i = 0;
	while (i < num_of_philos)
	{
		if (philo_done_eating(&philos[i++]) == false)
			return (false);
	}
	return (true);
}
