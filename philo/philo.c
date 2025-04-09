/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:29:09 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/09 19:43:10 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
#include <pthread.h>

void	print_usage(void)
{
	printf("Usage: \n");
	printf(" philo \n");
	printf("    [number_of_philosophers]\n");
	printf("    [time_to_die_in_milliseconds] >= 60\n");
	printf("    [time_to_eat_in_milliseconds] >= 60\n");
	printf("    [time_to_sleep_in_milliseconds] >= 60\n");
	printf("    [Optional : Number_of_times_all_the_philosophers_need_to_eat]\n");
	printf(" philo only accept positive numbers\n");
        printf(" max number of philosophers : 200\n");
}

bool	isvalid_args(int argc, char **argv)
{
	if ((argc != 4 && argc != 5))
		return (false);
	while (*argv)
	{
		if (isvalid_number(*argv) == false)
			return (false);
		argv++;
	}
	return (true);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s)
		(void)!write(fd, s++, 1);
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
	ssize_t	current_time_ms;

	current_time_ms = get_current_time();
	if (current_time_ms == -1)
		return (-1);
	return (current_time_ms - start_time);
}

bool	init_info(t_info *info, char **data)
{
	info->death_flag = false;
	info->num_of_philos = ft_atoi(data[0]);
        if (info->num_of_philos > 200)
                return false;
	info->time_to_die = ft_atoi(data[1]);
	info->time_to_eat = ft_atoi(data[2]);
	info->time_to_sleep = ft_atoi(data[3]);
	info->num_times_to_eat = 60;
	if (data[4] != NULL)
		info->num_times_to_eat = ft_atoi(data[4]);
	if (info->num_of_philos < 1 || info->time_to_die < 60
		|| info->time_to_eat < 60 || info->time_to_sleep < 60
		|| info->num_times_to_eat < 0)
		return (false);
	pthread_mutex_init(&info->dead_lock, NULL);
	pthread_mutex_init(&info->print_lock, NULL);
	return (true);
}

void	init_philo(t_info *info, t_philo *philo, size_t id)
{
	philo->id = id;
	philo->meals_eaten = 0;
	philo->num_times_to_eat = info->num_times_to_eat;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->time_to_die = info->time_to_die;
	(void)!(philo->done_eating = false);
	philo->dead = &info->death_flag;
	// get_current_time return -1 when fail
	philo->last_meal_time = get_current_time();
	philo->start_time = get_current_time();
	philo->print_lock = &info->print_lock;
	philo->dead_lock = &info->dead_lock;
	philo->r_fork = &info->forks[id - 1];
	philo->l_fork = &info->forks[id % info->num_of_philos];
	pthread_mutex_init(philo->l_fork, NULL);
	pthread_mutex_init(philo->r_fork, NULL);
        pthread_mutex_init(&philo->eating, NULL);
        pthread_mutex_init(&philo->done_eating_lock, NULL);
}

void	philo_sleep(t_philo *philo)
{
	if (pthread_mutex_lock(philo->print_lock) != 0)
		return ;
	printf("%zu %d is sleeping\n", get_current_timestamp(philo->start_time),
		philo->id);
	pthread_mutex_unlock(philo->print_lock);
	usleep(philo->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	if (pthread_mutex_lock(philo->print_lock) != 0)
		return ;
	printf("%zu %d is thinking\n", get_current_timestamp(philo->start_time),
		philo->id);
	pthread_mutex_unlock(philo->print_lock);
}

void	philo_eat(t_philo *philo)
{
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
	pthread_mutex_lock(philo->print_lock);
	printf("%zu %d is eating\n", get_current_timestamp(philo->start_time),
		philo->id);
	pthread_mutex_unlock(philo->print_lock);
        pthread_mutex_lock(&philo->eating);
	philo->last_meal_time = get_current_time();
        philo->meals_eaten++;
        pthread_mutex_unlock(&philo->eating);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
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
        bool done_eating;

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
        bool done;

	info = (t_info *)data;
	while (philos_done_eating(info->philos, info->num_of_philos) == false)
	{
		i = 0;
		while (i < info->num_of_philos && philos_done_eating(info->philos,
				info->num_of_philos) == false)
		{
                        pthread_mutex_lock(&info->philos[i].eating);
			time_difference = get_current_time()
				- info->philos[i].last_meal_time;
                        done = info->philos[i].done_eating == true;
                        pthread_mutex_unlock(&info->philos[i].eating);

			if (time_difference > info->time_to_die
				&& done == false)
			{
				info->death_flag = true;
				pthread_mutex_lock(&info->print_lock);
				printf("%zu %d died\n",
					get_current_timestamp(info->philos[i].start_time),
					info->philos[i].id);
				/* clean(info); */
				return (NULL);
			}
			i++;
		}
	}
	/* clean(info); */
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
		init_philo(&info, &info.philos[i], i + 1);
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
