/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:29:24 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/22 14:58:21 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	set_sem_name(char *sem_name, char *name, char *philo_id)
{
	ft_strcpy(sem_name, name);
	ft_strcat(sem_name, philo_id);
}

static void	init_philo_sem(char *sem_name, char **philo_sem_name, sem_t *sem)
{
	*philo_sem_name = sem_name;
	safe_sem_open(&sem, *philo_sem_name, 1);
}

static bool	philo_sem(t_philo *philo)
{
	char	sem_name[100];
	char	strphilo_id[5];
	char	*_strphilo_id;

	_strphilo_id = ft_itoa(philo->id);
	if (_strphilo_id == NULL)
		return (false);
	memset(sem_name, 0, sizeof(sem_name));
	memset(strphilo_id, 0, sizeof(strphilo_id));
	ft_strcpy(strphilo_id, _strphilo_id);
	_strphilo_id = (free(_strphilo_id), NULL);
	set_sem_name(sem_name, "is_eating_lock_", strphilo_id);
	init_philo_sem(sem_name, &philo->is_eating_sem_name, philo->is_eating_lock);
	set_sem_name(sem_name, "done_eating_lock_", strphilo_id);
	init_philo_sem(sem_name, &philo->done_eating_sem_name,
		philo->done_eating_lock);
	set_sem_name(sem_name, "dead_lock_", strphilo_id);
	init_philo_sem(sem_name, &philo->dead_sem_name, philo->dead_lock);
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
	(void)!(philo->is_sleeping = philo->done_eating = philo->is_eating = false);
	philo->dead = false;
	philo->last_meal_time = get_current_time();
	philo->start_time = get_current_time();
	philo->forks = info->forks;
	philo->print_lock = info->print_lock;
	if (philo_sem(philo) == false)
		return (false);
	return (true);
}
