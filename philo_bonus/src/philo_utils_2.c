/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:15:14 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/22 14:30:45 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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
	ssize_t	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		if (info->philos[i].pid == child_pid
			|| info->philos[i].done_eating == true)
			continue ;
		if (kill(info->philos[i].pid, SIGSTOP) == -1)
		{
			ft_fprintf(STDERR_FILENO, "ERROR: Kill to pid: %d\n", child_pid);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
