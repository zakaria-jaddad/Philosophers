/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:52:45 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/22 14:55:11 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	init_philos(t_info *info)
{
	ssize_t	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		init_philo(info, &info->philos[i], i + 1);
		i++;
	}
}

void	philo_process(t_philo *philo)
{
	pthread_t	observer;

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

void	wait_for_philos(t_info *info)
{
	t_philo	*philo;
	int		status;
	pid_t	child_pid;
	ssize_t	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		child_pid = sage_waitpid(&status);
		if (WEXITSTATUS(status) == PHILO_DONE_EATING)
		{
			philo = get_philo_by_pid(info, child_pid);
			if (philo == NULL)
				break ;
			philo->done_eating = true;
			continue ;
		}
		if (WEXITSTATUS(status) != PHILO_DONE_EATING)
		{
			kill_all_philos(info, child_pid);
			break ;
		}
		i++;
	}
	sem_clean(info);
}

int	main(int argc, char **argv)
{
	t_info	info;
	pid_t	pid;
	ssize_t	i;

	i = 0;
	if (isvalid_args(--argc, ++argv) == false)
		return (print_usage(), EXIT_FAILURE);
	if (init_info(&info, argv) == false)
		return (print_usage(), EXIT_FAILURE);
	init_philos(&info);
	while (i < info.num_of_philos)
	{
		pid = safe_fork();
		if (pid == 0)
			philo_process(&info.philos[i]);
		else
			info.philos[i++].pid = pid;
	}
	wait_for_philos(&info);
	return (EXIT_SUCCESS);
}
