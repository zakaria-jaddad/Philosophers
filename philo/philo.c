/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:29:09 by zajaddad          #+#    #+#             */
/*   Updated: 2025/03/27 01:26:44 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"


void	print_usage(int exit_code)
{
	printf("Usage: \n");
	printf(" ./philo \n");
	printf("    [number_of_philosophers]\n");
	printf("    [time_to_die_in_milliseconds]\n");
	printf("    [time_to_eat_in_milliseconds]\n");
	printf("    [time_to_sleep_in_milliseconds]\n");
	printf("    [Optional : Number_of_times_all_the_philosophers_need_to_eat]\n");
	exit(exit_code);
}

bool	isvalid_args(int argc, char **argv)
{
	if ((argc != 4 && argc != 5) || argv == NULL)
		return (false);
	while (*argv)
	{
		if (isvalid_number(*argv) == false)
			return (false);
		argv++;
	}
	return (true);
}
void  init_info(t_info *info, char **data)
{
  info->dead_flag = false;
  info->num_of_philos = ft_atoll(data[0]);
}

int	main(int argc, char **argv)
{
  t_info info;

	if (isvalid_args(--argc, ++argv) == false)
    print_usage(EXIT_FAILURE);
  init_info(&info, argv);
  return (EXIT_SUCCESS);
}
