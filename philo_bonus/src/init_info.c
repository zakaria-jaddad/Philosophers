/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:25:14 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 20:25:34 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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
	safe_sem_open(&info->forks, "forks", info->num_of_philos);
	safe_sem_open(&info->print_lock, "print_lock", 1);
	return (true);
}
