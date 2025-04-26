/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:27:31 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/26 02:36:18 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static ssize_t	get_time_difference(t_philo *philo)
{
	ssize_t	current_time;
	ssize_t	time_difference;

	current_time = get_current_time();
	if (current_time == -1)
		return (ft_fprintf(STDERR_FILENO, "ERROR: gettimeofday\n"), -1);
	if (pthread_mutex_lock(&philo->eating) != 0)
		return (ft_fprintf(STDERR_FILENO,
				"ERROR: locking eating mutex in observe\n"), -1);
	time_difference = current_time - philo->last_meal_time;
	if (pthread_mutex_unlock(&philo->eating) != 0)
		return (ft_fprintf(STDERR_FILENO,
				"ERROR: unlocking eating mutex in observe\n"), -1);
	return (time_difference);
}

void	*philo_died(t_philo *philo)
{
	safe_print("%zu %d died\n", philo);
	if (pthread_mutex_lock(philo->dead_lock) != 0)
		return (ft_fprintf(STDERR_FILENO,
				"ERROR: locking dead mutexin observer\n"), NULL);
	*(philo->dead) = true;
	if (pthread_mutex_unlock(philo->dead_lock) != 0)
		return (ft_fprintf(STDERR_FILENO,
				"ERROR: unlocking dead mutex in observer\n"), NULL);
	return (NULL);
}

void	*observe(void *data)
{
	t_info	*info;
	ssize_t	i;
	ssize_t	time_difference;
	t_philo	*philo;

	info = (t_info *)data;
	while (philos_done_eating(info->philos, info->num_of_philos) == false)
	{
		i = 0;
		while (i < info->num_of_philos)
		{
			philo = &info->philos[i++];
			time_difference = get_time_difference(philo);
			if (time_difference == -1)
				return (ft_fprintf(STDERR_FILENO, "ERROR: time difference\n"),
					NULL);
			if (time_difference > philo->time_to_die
				&& philo_done_eating(philo) == false)
				return (philo_died(philo));
		}
	}
	return (NULL);
}
