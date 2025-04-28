/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:04:29 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/28 19:25:09 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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
	exit(EXIT_FAILURE);
}

void	safe_print(char *s, t_philo *philo)
{
	if (check_philo_death(philo) == true)
		return ;
	safe_sem_wait(philo->print_lock, philo);
	printf(s, get_current_timestamp(philo->start_time), philo->id);
	safe_sem_post(philo->print_lock);
}
