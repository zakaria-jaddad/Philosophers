/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:16:04 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/23 23:51:46 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	init_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
		if (pthread_mutex_init(&info->forks[i++], NULL) != 0)
			return (ft_fprintf(STDERR_FILENO,
					"ERROR: fork mutex initialization\n"), false);
	return (true);
}
