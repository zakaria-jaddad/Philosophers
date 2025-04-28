/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:01:45 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/29 00:31:38 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	safe_sem_open(sem_t **sem, char *sem_name, unsigned int value)
{
	sem_unlink(sem_name);
	*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0677, value);
	if (*sem == SEM_FAILED)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Semaphore Initialization\n");
		exit(EXIT_FAILURE);
	}
}

void	safe_sem_wait(sem_t *sem, t_philo *philo)
{
	if (check_philo_death(philo) == true)
		return ;
	if (sem_wait(sem) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Locking Semaphore\n");
		exit(EXIT_FAILURE);
	}
}

void	safe_sem_post(sem_t *sem)
{
	if (sem_post(sem) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Unlocking Semaphore\n");
		exit(EXIT_FAILURE);
	}
}

void	safe_sem_close(sem_t *sem)
{
	if (sem_close(sem) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR Semaphore Closing\n");
		exit(EXIT_FAILURE);
	}
}

void	safe_sem_unlink(char *sem_name)
{
	if (sem_unlink(sem_name) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR Semaphore Unlinking\n");
		exit(EXIT_FAILURE);
	}
}
