/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:29:09 by zajaddad          #+#    #+#             */
/*   Updated: 2025/03/28 02:31:03 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	print_usage(int exit_code)
{
	printf("Usage: \n");
	printf(" philo \n");
	printf("    [number_of_philosophers]\n");
	printf("    [time_to_die_in_milliseconds]\n");
	printf("    [time_to_eat_in_milliseconds]\n");
	printf("    [time_to_sleep_in_milliseconds]\n");
	printf("    [Optional : Number_of_times_all_the_philosophers_need_to_eat]\n");
	printf(" philo Only accept positive numbers\n");
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

void	init_info(t_info *info, t_philo *philos, char **data)
{
	info->dead_flag = false;
	info->num_of_philos = ft_atoll(data[0]);
	info->time_to_die = ft_atoll(data[1]);
	info->time_to_eat = ft_atoll(data[2]);
	info->time_to_sleep = ft_atoll(data[3]);
	info->num_times_to_eat = 60;
	if (data[4] != NULL)
		info->num_times_to_eat = ft_atoll(data[4]);
	info->philos = philos;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philos);
	if (info->forks == NULL)
		return ;
	pthread_mutex_init(&info->dead_lock, NULL);
	pthread_mutex_init(&info->write_lock, NULL);
	pthread_mutex_init(&info->meal_lock, NULL);
}

void	init_philo(t_info *info, t_philo *philo, int id)
{
	philo->id = id;
	philo->meals_eaten = 0;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->time_to_die = info->time_to_die;
	(void)!(philo->is_eating = philo->is_sleeping = false);
	*philo->dead = info->dead_flag;
	philo->is_thinking = true;
	philo->write_lock = &info->write_lock;
	philo->meal_lock = &info->meal_lock;
	philo->dead_lock = &info->dead_lock;
	philo->l_fork = &info->forks[id - 1];
	if (id == info->num_of_philos)
		philo->r_fork = &info->forks[0];
	else
		philo->r_fork = &info->forks[id];
}

void	philo_sleep(t_philo *philo)
{
	printf("%d is sleeping\n", philo->id);
	usleep(philo->time_to_sleep);
	philo->is_sleeping = false;
	philo->is_thinking = true;
}

void	philo_think(t_philo *philo)
{
	printf("%d is thinking\n", philo->id);
	philo->is_thinking = false;
	philo->is_eating = true;
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	printf("%d is eating\n", philo->id);
	usleep((philo->meals_eaten++, philo->time_to_eat));
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->is_eating = false;
	philo->is_thinking = true;
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->dead)
	{
		if (philo->is_sleeping == true)
			philo_sleep(philo);
		if (philo->is_thinking == true)
			philo_think(philo);
		if (philo->is_eating == true)
			philo_eat(philo);
		if (philo->meals_eaten == philo->num_times_to_eat)
			break ;
	}
	return (NULL);
}

bool	done_eating(t_philo *philos, size_t num_of_philos)
{
	size_t	i;

	i = 0;
	while (i < num_of_philos)
	{
		if (philos[i].meals_eaten != philos[i].num_times_to_eat)
			return (false);
	}
	return (true);
}

void	*observe(void *data)
{
	t_info	*info;

	info = (t_info *)data;
	while (info->dead_flag == false)
		if (done_eating(info->philos, info->num_of_philos) == true)
			info->dead_flag = true;
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	observer;
	t_philo		philos[MAX_PHILOS];

	if (isvalid_args(--argc, ++argv) == false)
		print_usage(EXIT_FAILURE);
	init_info(&info, philos, argv);
	pthread_create(&observer, NULL, observe, &info);
	for (int i = 0; i < info.num_of_philos; i++)
	{
		init_philo(&info, &info.philos[i], i + 1);
		pthread_create(&info.philos[i].thread, NULL, philo_routine,
			&info.philos[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
