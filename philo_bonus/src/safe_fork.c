/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:54:20 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/22 14:54:59 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

pid_t	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_fprintf(2, "ERROR: Process Creation");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

pid_t	sage_waitpid(int *status)
{
	pid_t	child_pid;

	child_pid = waitpid(-1, status, 0);
	if (child_pid == -1)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Waitpid\n");
		exit(EXIT_FAILURE);
	}
	return (child_pid);
}
