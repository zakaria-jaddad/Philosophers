/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:57:47 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/23 23:39:00 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	init_philo_mutexes(t_philo *philo)
{
	if (pthread_mutex_init(&philo->eating, NULL) != 0)
		return (ft_fprintf(STDERR_FILENO,
				"ERROR: eating mutex initialization in philo %d\n", philo->id),
			false);
	if (pthread_mutex_init(&philo->done_eating_lock, NULL) != 0)
		return (ft_fprintf(STDERR_FILENO,
				"ERROR: done eating mutex initialization in philo %d\n",
				philo->id), false);
	return (true);
}

bool	init_philo(t_info *info, t_philo *philo, size_t id)
{
	philo->id = id;
	philo->meals_eaten = 0;
	philo->num_times_to_eat = info->num_times_to_eat;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->time_to_die = info->time_to_die;
	(void)!(philo->done_eating = false);
	philo->dead = &info->death_flag;
	philo->last_meal_time = get_current_time();
	philo->start_time = get_current_time();
	if (philo->last_meal_time == -1 || philo->start_time == -1)
		return (ft_fprintf(STDERR_FILENO, "ERROR: gettimeofday\n"), false);
	philo->print_lock = &info->print_lock;
	philo->dead_lock = &info->dead_lock;
	philo->l_fork = &info->forks[id - 1];
	philo->r_fork = &info->forks[id % info->num_of_philos];
	if (init_philo_mutexes(philo) == false)
		return (false);
	return (true);
}
