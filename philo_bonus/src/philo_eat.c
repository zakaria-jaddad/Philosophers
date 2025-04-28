/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:13:59 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/28 19:14:21 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	safe_sem_wait(philo->forks, philo);
	safe_print("%zu %d has taken a fork\n", philo);
	safe_sem_wait(philo->forks, philo);
	safe_print("%zu %d has taken a fork\n", philo);
	safe_print("%zu %d is eating\n", philo);
	safe_sem_wait(philo->is_eating_lock, philo);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	safe_sem_post(philo->is_eating_lock);
	ft_usleep(philo->time_to_eat);
	safe_sem_post(philo->forks);
	safe_sem_post(philo->forks);
}
