/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:26:21 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/20 13:12:11 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdbool.h>
#include <stdio.h>

void	print_usage(void)
{
	ft_fprintf(STDERR_FILENO, "Usage: \n");
	ft_fprintf(STDERR_FILENO, " philo \n");
	ft_fprintf(STDERR_FILENO, "    [number_of_philosophers]\n");
	ft_fprintf(STDERR_FILENO, "    [time_to_die_in_milliseconds] >= 60\n");
	ft_fprintf(STDERR_FILENO, "    [time_to_eat_in_milliseconds] >= 60\n");
	ft_fprintf(STDERR_FILENO, "    [time_to_sleep_in_milliseconds] >= 60\n");
	ft_fprintf(STDERR_FILENO,
		"    [Optional : Number_of_times_all_the_philosophers_need_to_eat]\n");
	ft_fprintf(STDERR_FILENO, " philo only accept positive numbers\n");
	ft_fprintf(STDERR_FILENO, " max number of philosophers : 200\n");
}

bool	safe_print(char *s, t_philo *philo)
{
	if (pthread_mutex_lock(philo->print_lock) != 0)
		return ((void)ft_fprintf(STDERR_FILENO,
				"ERROR: locking print mutex in philo %d", philo->id), false);
	/* printf("check deathc: %s\n", check_death(philo) == true ? "true" : "false"); */
	if (check_death(philo) == true)
	{
		if (pthread_mutex_unlock(philo->print_lock) != 0)
			return ((void)ft_fprintf(STDERR_FILENO,
					"ERROR: unlocking print mutex in philo %d", philo->id), false);
		return false;
	}
	printf(s, get_current_timestamp(philo->start_time), philo->id);
	if (pthread_mutex_unlock(philo->print_lock) != 0)
		return ((void)ft_fprintf(STDERR_FILENO,
				"ERROR: unlocking print mutex in philo %d", philo->id), false);
	return (true);
}

int	print_error(char *err)
{
	return (ft_fprintf(STDERR_FILENO, err), EXIT_FAILURE);
}
