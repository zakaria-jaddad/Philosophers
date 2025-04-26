/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:08:40 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/25 23:22:40 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (true)
	{
		(void)(philo_eat(philo), philo_sleep(philo), philo_think(philo));
		if (philo->meals_eaten == philo->num_times_to_eat)
		{
			if (pthread_mutex_lock(&philo->done_eating_lock) != 0)
				return (ft_fprintf(STDERR_FILENO, "ERROR: locking done_eating "
						"mutex in philo %d\n", philo->id), NULL);
			philo->done_eating = true;
			if (pthread_mutex_unlock(&philo->done_eating_lock) != 0)
				return (ft_fprintf(STDERR_FILENO, "ERROR: unlocking "
						"done_eating mutex in philo %d\n", philo->id), NULL);
			break ;
		}
	}
	return (NULL);
}
