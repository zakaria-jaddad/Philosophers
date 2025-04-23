/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:49:27 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/23 14:51:57 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	init_info(t_info *info, char **data)
{
	info->death_flag = false;
	info->num_of_philos = ft_atoi(data[0]);
	if (info->num_of_philos > 200)
		return (false);
	info->time_to_die = ft_atoi(data[1]);
	info->time_to_eat = ft_atoi(data[2]);
	info->time_to_sleep = ft_atoi(data[3]);
	if (data[4] != NULL)
	{
		info->num_times_to_eat = ft_atoi(data[4]);
		if (info->num_times_to_eat < 1)
			return (false);
	}
	if (info->num_of_philos < 1 || info->time_to_die < 60
		|| info->time_to_eat < 60 || info->time_to_sleep < 60)
		return (false);
	if (pthread_mutex_init(&info->dead_lock, NULL) != 0)
		return (ft_fprintf(STDERR_FILENO, "ERROR: dead mutex initialization\n"),
			false);
	if (pthread_mutex_init(&info->print_lock, NULL) != 0)
		return (ft_fprintf(STDERR_FILENO,
				"ERROR: print mutex initialization\n"), false);
	return (true);
}
