/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:38:37 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/20 12:58:03 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_sleep(t_philo *philo)
{
	if (safe_print("%zu %d is sleeping\n", philo) == false)
		return ;
	ft_usleep(philo->time_to_sleep);
}
