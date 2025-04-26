/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:29:09 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/26 02:37:04 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

/* int	clean(t_info *info) */
/* { */
/* 	ssize_t	i; */
/**/
/* 	i = 0; */
/* 	while (i < info->num_of_philos) */
/* 	{ */
/* 		if (pthread_detach(info->philos[i].thread) != 0) */
/* 			return (ft_fprintf(STDERR_FILENO, "ERROR: thread detach in philo */
/* 					%d\n", info->philos[i].id), EXIT_FAILURE); */
/* 	} */
/* 	return (EXIT_SUCCESS); */
/* } */

int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	observer;

	if (isvalid_args(--argc, ++argv) == false)
		return (print_usage(), EXIT_FAILURE);
	if (init_info(&info, argv) == false)
		return (EXIT_FAILURE);
	if (init_philos(&info) == false)
		return (print_error("ERROR: initilazing philos\n"));
	if (pthread_create(&observer, NULL, observe, &info) != 0)
		return (print_error("ERROR: creating observer\n"));
	if (start_philos(&info) == false)
		return (print_error("ERROR: creating philos\n"));
	if (pthread_join(observer, NULL) != 0)
		return (print_error("ERROR: joining observer\n"));
	/* return (clean(&info)); */
	return (EXIT_SUCCESS);
}
