/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:37:42 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/29 00:37:43 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	sem_clean(t_info *info)
{
	safe_sem_unlink("/forks");
	safe_sem_close(info->forks);
	safe_sem_unlink("/print_lock");
	safe_sem_close(info->print_lock);
	safe_sem_unlink("/dead_lock");
	safe_sem_close(info->dead_lock);
}

void	wait_for_philos(t_info *info)
{
	ssize_t	i;
	int		status;
	pid_t	child_pid;
	t_philo	*philo;

	i = 0;
	while (i < info->num_of_philos)
	{
		child_pid = waitpid(-1, &status, 0);
		if (child_pid == -1)
			break ;
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
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (isvalid_args(--argc, ++argv) == false)
		print_usage();
	if (init_info(&info, argv) == false)
		print_usage();
	init_philos(&info);
	wait_for_philos(&info);
	sem_clean(&info);
	return (EXIT_SUCCESS);
}
