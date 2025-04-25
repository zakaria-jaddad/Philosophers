/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:29:09 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/25 16:23:09 by zajaddad         ###   ########.fr       */
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
		return (print_error("ERROR: initilazing forks\n"));
	if (init_philos(&info) == false)
		return (print_error("ERROR: initilazing philos\n"));
	if (pthread_create(&observer, NULL, observe, &info) != 0)
		return (print_error("ERROR: creating observer\n"));
	if (start_philos(&info) == false)
		return (print_error("ERROR: creating philos\n"));
	if (pthread_join(observer, NULL) != 0)
		return (print_error("ERROR: joining observer\n"));
	return (EXIT_SUCCESS);
}
