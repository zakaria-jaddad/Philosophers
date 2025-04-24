/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:29:09 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/24 00:28:05 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	observer;

	if (isvalid_args(--argc, ++argv) == false)
		return (print_usage(), EXIT_FAILURE);
	if (init_info(&info, argv) == false)
		return (print_usage(), EXIT_FAILURE);
	if (init_forks(&info) == false)
		return (EXIT_FAILURE);
	for (ssize_t i = 0; i < info.num_of_philos; i++)
	{
		if (init_philo(&info, &info.philos[i], i + 1) == false)
			return (EXIT_FAILURE);
	}
	pthread_create(&observer, NULL, observe, &info);
	for (ssize_t i = 0; i < info.num_of_philos; i++)
		pthread_create(&info.philos[i].thread, NULL, philo_routine,
			&info.philos[i]);
	pthread_join(observer, NULL);
	return (EXIT_SUCCESS);
}

/* void	clean(t_info *info) */
/* { */
/* 	pthread_mutex_destroy(&info->print_lock); */
/* 	pthread_mutex_destroy(&info->dead_lock); */
/* 	//  destroy all locks */
/* 	for (int j = 0; j < (int)info->num_of_philos; j++) */
/* 	{ */
/* 		pthread_mutex_destroy(info->philos[j].l_fork); */
/* 		pthread_mutex_destroy(info->philos[j].r_fork); */
/* 		pthread_mutex_destroy(&info->philos[j].eating); */
/* 	} */
/* } */
