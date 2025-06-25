/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:41:01 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/25 09:16:52 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"
#include <stdio.h>

static void	init_philo_sem(t_philo *philo)
{
	char	sem_name[100];
	char	strphilo_id[5];
	char	*philo_id;

	memset(sem_name, 0, sizeof(sem_name));
	memset(strphilo_id, 0, sizeof(strphilo_id));
	philo_id = ft_itoa(philo->id);
	if (philo_id == NULL)
		return ;
	ft_strcpy(strphilo_id, philo_id);
	philo_id = (free(philo_id), NULL);
	ft_strcpy(sem_name, "is_eating_lock_");
	ft_strcat(sem_name, strphilo_id);
	philo->is_eating_sem_name = sem_name;
	safe_sem_open(&philo->is_eating_lock, sem_name, 1);
	ft_strcpy(sem_name, "done_eating_lock_");
	ft_strcat(sem_name, strphilo_id);
	philo->done_eating_sem_name = sem_name;
	safe_sem_open(&philo->done_eating_lock, sem_name, 1);
}

void	clean_philo_sem(t_philo *philo)
{
	safe_sem_close(philo->is_eating_lock);
	safe_sem_close(philo->done_eating_lock);
}

static void	philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (check_philo_death(philo) == false)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (philo->meals_eaten == philo->num_times_to_eat)
		{
			safe_sem_wait(philo->done_eating_lock, philo);
			philo->done_eating = true;
			safe_sem_post(philo->done_eating_lock);
			clean_philo_sem(philo);
			exit(PHILO_DONE_EATING);
		}
	}
	clean_philo_sem(philo);
	exit(PHILO_DIED);
}

static void	*observe(void *data)
{
	t_philo	*philo;
	ssize_t	time_difference;

	philo = (t_philo *)data;
	while (philo_done_eating(philo) == false)
	{
		safe_sem_wait(philo->is_eating_lock, philo);
		time_difference = get_current_time() - philo->last_meal_time;
		safe_sem_post(philo->is_eating_lock);
		if (time_difference > philo->time_to_die)
		{
			safe_sem_wait(philo->print_lock, philo);
			printf("%zu %d died\n", get_current_timestamp(philo->start_time),
				philo->id);
			safe_sem_wait(philo->dead_lock, philo);
			philo->dead = true;
			clean_philo_sem(philo);
			exit(PHILO_DIED);
		}
		usleep(500);
	}
	clean_philo_sem(philo);
	exit(PHILO_DONE_EATING);
}

void	philo_dine(t_philo *philo)
{
	pthread_t	observer;

	init_philo_sem(philo);
	if (pthread_create(&observer, NULL, observe, philo) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Thread Creation");
		exit(EXIT_FAILURE);
	}
	if (pthread_detach(observer) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Thread Detaching");
		exit(EXIT_FAILURE);
	}
	philo_routine(philo);
}
