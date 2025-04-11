/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:05:50 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/10 18:39:29 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>

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

// TODO: initialize old mutexes
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
		|| info->num_times_to_eat < 60)
		return (false);
        info->dead_lock = 10;
        info->print_lock = 10;
	return (true);
        
}

// TODO: initialize old mutexes
void	init_philo(t_info *info, t_philo *philo, size_t id)
{
	philo->id = id;
	philo->meals_eaten = 0;
	philo->num_times_to_eat = info->num_times_to_eat;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->time_to_die = info->time_to_die;
	(void)!(philo->is_sleeping = philo->done_eating = philo->is_eating = false);
	philo->dead = &info->death_flag;
	// get_current_time return -1 when fail
        //
	philo->last_meal_time = get_current_time();
	philo->start_time = get_current_time();
	philo->print_lock = &info->print_lock;
	philo->dead_lock = &info->dead_lock;
	philo->r_fork = NULL;
	philo->l_fork = NULL;
        philo->meal_lock = 10;
}

void	philo_routine(t_philo *philo)
{

	if (philo->id % 2 == 0)
		usleep(500);
        printf("It's philo %d\n", philo->id);
	while (true)
	{
		/* philo_eat(philo); */
		/* philo_sleep(philo); */
		/* philo_think(philo); */
		/* if (philo->meals_eaten == philo->num_times_to_eat) */
		/* { */
			/* pthread_mutex_lock(&philo->done_eating_lock); */
			/* philo->done_eating = true; */
			/* pthread_mutex_unlock(&philo->done_eating_lock); */
			/* break ; */
		/* } */
	}
}

/*
 *  TODO: 
 *  [ ] Forks in the middle of the table
 *
*/
int	main(int argc, char **argv)
{
	t_info		info;

	if (isvalid_args(--argc, ++argv) == false)
		return (print_usage(), EXIT_FAILURE);
	if (init_info(&info, argv) == false)
		return (print_usage(), EXIT_FAILURE);
	for (ssize_t i = 0; i < info.num_of_philos; i++)
		init_philo(&info, &info.philos[i], i + 1);


        // NOTE: 
        for (ssize_t i = 0; i < info.num_of_philos; i++) {
                // create a process aka philosopher
                pid_t pid = fork();

                // TODO: child routine of philo
                if (pid == 0) {
                        info.philos[i].pid = getpid();
                        philo_routine(&info.philos[i]);
                        return (EXIT_FAILURE);
                }
        }
        // Parent process should wait for children
        int status;
        wait(&status);
        printf("This is the parent process id: %d, this is the state of the last child process %s\n", getpid(), (WIFEXITED(status) != 0) ? "true" : "false");
	return (EXIT_SUCCESS);
}
