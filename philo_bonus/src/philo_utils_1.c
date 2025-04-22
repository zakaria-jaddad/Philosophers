/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:10:30 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 20:13:47 by zajaddad         ###   ########.fr       */
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

void	philo_sleep(t_philo *philo)
{
	safe_print("%zu %d is sleeping\n", philo);
	ft_usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	safe_print("%zu %d is thinking\n", philo);
}

void	philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(500);
	while (true)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (philo->meals_eaten == philo->num_times_to_eat)
		{
			safe_sem_wait(philo->done_eating_lock, philo);
			philo->done_eating = true;
			safe_sem_post(philo->done_eating_lock);
			exit(PHILO_DONE_EATING);
		}
		if (check_death(philo) == true)
			exit(PHILO_DIED);
	}
}

void	*observe(void *data)
{
	t_philo	*philo;
	ssize_t	time_difference;

	philo = (t_philo *)data;
	while (true)
	{
		if (check_done_eating(philo) == true)
			exit(PHILO_DONE_EATING);
		safe_sem_wait(philo->is_eating_lock, philo);
		time_difference = get_current_time() - philo->last_meal_time;
		safe_sem_post(philo->is_eating_lock);
		if (time_difference > philo->time_to_die
			&& check_done_eating(philo) == false)
		{
			safe_sem_wait(philo->print_lock, philo);
			printf("%zu %d died\n", get_current_timestamp(philo->start_time),
				philo->id);
			safe_sem_wait(philo->dead_lock, philo);
			philo->dead = true;
			safe_sem_post(philo->dead_lock);
			exit(PHILO_DIED);
		}
	}
	return (NULL);
}
