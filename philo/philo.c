/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:29:09 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/23 14:50:03 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

bool	init_philo(t_info *info, t_philo *philo, size_t id)
{
	philo->id = id;
	philo->meals_eaten = 0;
	philo->num_times_to_eat = info->num_times_to_eat;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->time_to_die = info->time_to_die;
	(void)!(philo->done_eating = false);
	philo->dead = &info->death_flag;
	philo->last_meal_time = get_current_time();
	philo->start_time = get_current_time();
	if (philo->last_meal_time == -1 || philo->start_time == -1)
		return (ft_fprintf(STDERR_FILENO, "ERROR: gettimeofday\n"), false);
	philo->print_lock = &info->print_lock;
	philo->dead_lock = &info->dead_lock;
	philo->l_fork = &info->forks[id - 1];
	philo->r_fork = &info->forks[id % info->num_of_philos];
	pthread_mutex_init(philo->l_fork, NULL);
	pthread_mutex_init(philo->r_fork, NULL);
	pthread_mutex_init(&philo->eating, NULL);
	pthread_mutex_init(&philo->done_eating_lock, NULL);
	return (true);
}

void	philo_sleep(t_philo *philo)
{
	safe_print("%zu %d is sleeping\n", philo);
	ft_usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	safe_print("%zu %d is thinking\n", philo);
}

void	philo_eat(t_philo *philo)
{
	ssize_t	last_meal_time;

	if (pthread_mutex_lock(philo->r_fork) == 0)
	{
		pthread_mutex_lock(philo->print_lock);
		printf("%zu %d has taken a fork\n",
			get_current_timestamp(philo->start_time), philo->id);
		pthread_mutex_unlock(philo->print_lock);
	}
	if (pthread_mutex_lock(philo->l_fork) == 0)
	{
		pthread_mutex_lock(philo->print_lock);
		printf("%zu %d has taken a fork\n",
			get_current_timestamp(philo->start_time), philo->id);
		pthread_mutex_unlock(philo->print_lock);
	}
	safe_print("%zu %d is eating\n", philo);
	pthread_mutex_lock(&philo->eating);
	last_meal_time = get_current_time();
	if (last_meal_time == -1)
		return ((void)ft_fprintf(STDERR_FILENO, "ERROR: gettimeofday\n"));
	philo->last_meal_time = last_meal_time;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->eating);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// will fail
	pthread_detach(philo->thread);
	if (philo->id % 2 == 0)
		usleep(500);
	while (true)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (philo->meals_eaten == philo->num_times_to_eat)
		{
			pthread_mutex_lock(&philo->done_eating_lock);
			philo->done_eating = true;
			pthread_mutex_unlock(&philo->done_eating_lock);
			break ;
		}
	}
	return (NULL);
}

bool	philos_done_eating(t_philo *philos, size_t num_of_philos)
{
	size_t	i;
	bool	done_eating;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_lock(&philos[i].done_eating_lock);
		done_eating = philos[i].done_eating == false;
		pthread_mutex_unlock(&philos[i].done_eating_lock);
		if (done_eating)
			return (false);
		i++;
	}
	return (true);
}

void	*observe(void *data)
{
	t_info	*info;
	ssize_t	i;
	ssize_t	time_difference;
	bool	done;
	ssize_t	current_time;

	info = (t_info *)data;
	while (philos_done_eating(info->philos, info->num_of_philos) == false)
	{
		i = 0;
		while (i < info->num_of_philos && philos_done_eating(info->philos,
				info->num_of_philos) == false)
		{
			current_time = get_current_time();
			if (current_time == -1)
				return (ft_fprintf(STDERR_FILENO, "ERROR: gettimeofday\n"),
					NULL);
			pthread_mutex_lock(&info->philos[i].eating);
			time_difference = current_time - info->philos[i].last_meal_time;
			pthread_mutex_unlock(&info->philos[i].eating);
			pthread_mutex_lock(&info->philos[i].done_eating_lock);
			done = info->philos[i].done_eating == true;
			pthread_mutex_unlock(&info->philos[i].done_eating_lock);
			if (time_difference > info->time_to_die && done == false)
			{
				safe_print("%zu %d died\n", &info->philos[i]);
				pthread_mutex_lock(&info->dead_lock);
				info->death_flag = true;
				pthread_mutex_unlock(&info->dead_lock);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	observer;

	if (isvalid_args(--argc, ++argv) == false)
		return (print_usage(), EXIT_FAILURE);
	if (init_info(&info, argv) == false)
		return (print_usage(), EXIT_FAILURE);
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
