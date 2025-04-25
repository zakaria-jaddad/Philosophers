/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:16:40 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/25 16:16:55 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	start_philos(t_info *info)
{
	ssize_t	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		if (pthread_create(&info->philos[i].thread, NULL, philo_routine,
				&info->philos[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}
