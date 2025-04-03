/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:29:09 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/03 10:44:10 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/_types/_ssize_t.h>

void	print_usage(void)
{
	printf("Usage: \n");
	printf(" philo \n");
	printf("    [number_of_philosophers]\n");
	printf("    [time_to_die_in_milliseconds]\n");
	printf("    [time_to_eat_in_milliseconds]\n");
	printf("    [time_to_sleep_in_milliseconds]\n");
	printf("    [Optional : Number_of_times_all_the_philosophers_need_to_eat]\n");
	printf(" philo Only accept positive numbers\n");
}

t_bool	isvalid_args(int argc, char **argv)
{
	if ((argc != 4 && argc != 5))
		return (False);
	while (*argv)
	{
		if (isvalid_number(*argv) == False)
			return (False);
		argv++;
	}
	return (True);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s)
		write(fd, s++, 1);
}

ssize_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_putstr_fd("ERROR: gettimeofday\n", 2), -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

ssize_t	get_current_timestamp(ssize_t start_time)
{
	ssize_t current_time_ms;

	current_time_ms = get_current_time();
	if (current_time_ms == -1)
		return -1;
	return (current_time_ms - start_time);
}

void	init_info(t_info *info, char **data)
{
	info->death_flag = False;
	info->num_of_philos = ft_atoll(data[0]);
	info->time_to_die = ft_atoll(data[1]);
	info->time_to_eat = ft_atoll(data[2]);
	info->time_to_sleep = ft_atoll(data[3]);
	info->num_times_to_eat = 60;
	if (data[4] != NULL)
		info->num_times_to_eat = ft_atoll(data[4]);
	pthread_mutex_init(&info->dead_lock, NULL);
	pthread_mutex_init(&info->print_lock, NULL);
	pthread_mutex_init(&info->meal_lock, NULL);
}

void	init_philo(t_info *info, t_philo *philo, size_t id)
{
	philo->id = id;
	philo->meals_eaten = 0;
	philo->num_times_to_eat = info->num_times_to_eat;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->time_to_die = info->time_to_die;
	(void)!(philo->is_thinking = philo->is_sleeping = philo->done_eating = False);
	philo->is_eating = True;
	philo->dead = &info->death_flag;

	// get_current_time return -1 when fail
	philo->last_meal_time = get_current_time();
	philo->start_time = get_current_time();
	philo->print_lock = &info->print_lock;
	philo->meal_lock = &info->meal_lock;
	philo->dead_lock = &info->dead_lock;
	philo->l_fork = &info->forks[id - 1];
	if (id == info->num_of_philos)
		philo->r_fork = &info->forks[0];
	else
		philo->r_fork = &info->forks[id];
	pthread_mutex_init(philo->l_fork, NULL);
	pthread_mutex_init(philo->r_fork, NULL);
}

void	philo_sleep(t_philo *philo)
{
	if (pthread_mutex_lock(philo->print_lock) != 0)
		return ;
	printf("%zu %d sleeping\n", get_current_timestamp(philo->start_time), philo->id);
	pthread_mutex_unlock(philo->print_lock);
	usleep(philo->time_to_sleep);
	philo->is_sleeping = False;
	philo->is_thinking = True;
}

void	philo_think(t_philo *philo)
{
	if (pthread_mutex_lock(philo->print_lock) != 0)
		return ;

	printf("%zu %d thinking\n", get_current_timestamp(philo->start_time), philo->id);
	pthread_mutex_unlock(philo->print_lock);
	philo->is_thinking = False;
	philo->is_eating = True;
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->r_fork) == 0)
		{
			pthread_mutex_lock(philo->print_lock);
			printf("%zu %d has taken a fork\n", get_current_timestamp(philo->start_time), philo->id);
			pthread_mutex_unlock(philo->print_lock);
		}
		if (pthread_mutex_lock(philo->l_fork) == 0)
		{

			pthread_mutex_lock(philo->print_lock);
			printf("%zu %d has taken a fork\n", get_current_timestamp(philo->start_time), philo->id);
			pthread_mutex_unlock(philo->print_lock);
		}
	}
	else 
	{
		if (pthread_mutex_lock(philo->l_fork) == 0)
		{
			pthread_mutex_lock(philo->print_lock);
			printf("%zu %d has taken a fork\n", get_current_timestamp(philo->start_time), philo->id);
			pthread_mutex_unlock(philo->print_lock);
		}
		if (pthread_mutex_lock(philo->r_fork) == 0)
		{

			pthread_mutex_lock(philo->print_lock);
			printf("%zu %d has taken a fork\n", get_current_timestamp(philo->start_time), philo->id);
			pthread_mutex_unlock(philo->print_lock);
		}
	}
	pthread_mutex_lock(philo->meal_lock);
	pthread_mutex_lock(philo->print_lock);
	printf("%zu %d eating\n", get_current_timestamp(philo->start_time), philo->id);
	usleep((philo->meals_eaten++, philo->time_to_eat * 1000));
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(philo->print_lock);
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->is_eating = False;
	philo->is_sleeping = True;
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (True)
	{
		if (philo->is_eating == True && *philo->dead == False)
			philo_eat(philo);
		if (philo->is_sleeping == True && *philo->dead == False)
			philo_sleep(philo);
		if (philo->is_thinking == True && *philo->dead == False)
			philo_think(philo);
		if (philo->meals_eaten == philo->num_times_to_eat)
		{
			pthread_mutex_lock(philo->print_lock);
			philo->done_eating = True;
			pthread_mutex_unlock(philo->print_lock);
			break ;
		}
	}
	return (NULL);
}

t_bool	philos_done_eating(t_philo *philos, size_t num_of_philos)
{
	size_t	i;

	i = 0;
	while (i < num_of_philos)
	{
		if (philos[i].done_eating == False)
			return (False);
		i++;
	}
	return (True);
}

void	*observe(void *data)
{
	t_info	*info;
	size_t	i;

	info = (t_info *)data;
	while (philos_done_eating(info->philos, info->num_of_philos) == False)
	{
		i = 0;
		while (i < info->num_of_philos)
		{
			if (get_current_time()
				- info->philos[i].last_meal_time >= info->time_to_die
				&& info->philos[i].done_eating == False)
			{
				pthread_mutex_lock(&info->dead_lock);
				pthread_mutex_lock(&info->print_lock);
				info->death_flag = True;
				printf("%zu %d died\n", get_current_timestamp(info->philos[i].start_time), info->philos[i].id);
				// Destroy data
				pthread_mutex_destroy(&info->dead_lock);
				pthread_mutex_destroy(&info->meal_lock);
				pthread_mutex_destroy(&info->dead_lock);
				return (NULL);
			}
			i++;
		}
	}
	// Destroy data
	pthread_mutex_destroy(&info->dead_lock);
	pthread_mutex_destroy(&info->meal_lock);
	pthread_mutex_destroy(&info->dead_lock);
	return (NULL);
}
/*
 * TODO:
 * Display timing in ms
 * Add mutexes from done eating variable
 * Handle overflow
 * */
int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	observer;

	if (isvalid_args(--argc, ++argv) == False)
		return (print_usage(), EXIT_FAILURE);
	init_info(&info, argv);
	for (size_t i = 0; i < info.num_of_philos; i++)
		init_philo(&info, &info.philos[i], i + 1);
	pthread_create(&observer, NULL, observe, &info);
	for (size_t i = 0; i < info.num_of_philos; i++)
		pthread_create(&info.philos[i].thread, NULL, philo_routine,
			&info.philos[i]);
	pthread_join(observer, NULL);
	return (EXIT_SUCCESS);
}
