/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:07:25 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/28 20:02:58 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

bool	philo_done_eating(t_philo *philo)
{
	bool	done;

	safe_sem_wait(philo->done_eating_lock, philo);
	done = philo->done_eating;
	safe_sem_post(philo->done_eating_lock);
	return (done);
}

t_philo	*get_philo_by_pid(t_info *info, pid_t pid)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		if (info->philos[i].pid == pid)
			return (&info->philos[i]);
		i++;
	}
	return (NULL);
}

void	kill_all_philos(t_info *info, pid_t child_pid)
{
	for (ssize_t i = 0; i < info->num_of_philos; i++)
	{
		if (info->philos[i].pid == child_pid
			|| info->philos[i].done_eating == true)
			continue ;
		if (kill(info->philos[i].pid, SIGSTOP) == -1)
		{
			ft_fprintf(STDERR_FILENO, "ERROR: Kill\n");
			exit(EXIT_FAILURE);
		}
	}
}

bool	check_philo_death(t_philo *philo)
{
	bool	dead;

	if (sem_wait(philo->dead_lock) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Locking Semaphore\n");
		exit(EXIT_FAILURE);
	}
	dead = philo->dead;
	if (sem_post(philo->dead_lock) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Unlocking Semaphore\n");
		exit(EXIT_FAILURE);
	}
	return (dead);
}
