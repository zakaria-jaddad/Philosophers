/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:16:48 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/28 19:27:43 by zajaddad         ###   ########.fr       */
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
	if (info->num_of_philos < 1 || info->time_to_die < 60
		|| info->time_to_eat < 60 || info->time_to_sleep < 60)
		return (print_usage(), false);
	info->num_times_to_eat = 0;
	if (data[4] != NULL)
	{
		info->num_times_to_eat = ft_atoi(data[4]);
		if (info->num_times_to_eat < 1)
			return (print_usage(), false);
	}
	safe_sem_open(&info->forks, "/forks", info->num_of_philos);
	safe_sem_open(&info->print_lock, "/print_lock", 1);
	safe_sem_open(&info->dead_lock, "/dead_lock", 1);
	return (true);
}
