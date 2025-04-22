/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:32 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 20:09:14 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	sem_clean(t_info *info)
{
	t_philo	*philo;
	ssize_t	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		philo = &info->philos[i];
		safe_sem_close(philo->dead_lock);
		safe_sem_unlinck(philo->dead_sem_name);
		safe_sem_close(philo->is_eating_lock);
		safe_sem_unlinck(philo->is_eating_sem_name);
		safe_sem_close(philo->done_eating_lock);
		safe_sem_unlinck(philo->done_eating_sem_name);
		i++;
	}
	safe_sem_close(info->forks);
	safe_sem_unlinck("forks");
	safe_sem_close(info->print_lock);
	safe_sem_unlinck("print_lock");
}
