/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:50:29 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/22 14:59:23 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: gettimeofday\n");
		exit(EXIT_FAILURE);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	get_current_timestamp(size_t start_time)
{
	return (get_current_time() - start_time);
}

void	ft_usleep(size_t ms)
{
	ssize_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(500);
}
