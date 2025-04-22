/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_done_eating.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:21:16 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 19:50:26 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

bool	check_done_eating(t_philo *philo)
{
	bool	done;

	safe_sem_wait(philo->done_eating_lock, philo);
	done = philo->done_eating;
	safe_sem_post(philo->done_eating_lock);
	return (done);
}
