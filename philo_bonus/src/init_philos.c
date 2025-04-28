/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:20:12 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/29 00:05:47 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	init_philo(t_info *info, t_philo *philo, size_t id)
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
	philo->dead_lock = info->dead_lock;
}

void	init_philos(t_info *info)
{
	ssize_t	i;
	pid_t	pid;

	i = 0;
	while (i < info->num_of_philos)
	{
		init_philo(info, &info->philos[i], i + 1);
		pid = fork();
                if (pid < 0) 
                {
                        ft_fprintf(2, "ERROR: Process Creation");
                        exit(EXIT_FAILURE);
                }
                if (pid == 0)
			philo_dine(&info->philos[i]);
                else
                        info->philos[i].pid = pid;
		i++;
	}
}
