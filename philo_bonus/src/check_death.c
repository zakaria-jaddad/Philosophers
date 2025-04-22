/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:20:36 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 18:20:52 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

bool	check_death(t_philo *philo)
{
	bool	dead;

	if (sem_wait(philo->dead_lock) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Locking Semaphore\n");
		exit(EXIT_FAILURE);
	}
	dead = philo->dead;
	if (sem_post(philo->dead_lock) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Unlocking Semaphore\n");
		exit(EXIT_FAILURE);
	}
	return (dead);
}
