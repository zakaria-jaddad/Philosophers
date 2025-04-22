/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:05:27 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/22 15:03:23 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "fprintf/ft_fprintf.h"
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_PHILOS 200
# define PHILO_DIED 3
# define PHILO_DONE_EATING 4

typedef struct s_philo
{
	pid_t	pid;
	int		id;
	bool	is_sleeping;
	size_t	meals_eaten;
	size_t	num_times_to_eat;
	size_t	last_meal_time;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	size_t	start_time;

	sem_t	*dead_lock;
	bool	dead;
	char	*dead_sem_name;

	sem_t	*print_lock;
	sem_t	*forks;

	bool	is_eating;
	sem_t	*is_eating_lock;
	char	*is_eating_sem_name;

	bool	done_eating;
	sem_t	*done_eating_lock;
	char	*done_eating_sem_name;
}			t_philo;

typedef struct s_info
{
	bool	death_flag;
	sem_t	*dead_lock;
	sem_t	*print_lock;
	sem_t	*forks;
	ssize_t	num_of_philos;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	num_times_to_eat;
	t_philo	philos[MAX_PHILOS];
}			t_info;

bool		isvalid_number(char *element);
ssize_t		ft_atoi(const char *str);
char		*ft_itoa(int n);
char		*ft_strcpy(char *s1, char *s2);
void		ft_strcat(char *des, const char *src);
bool		check_death(t_philo *philo);
bool		check_done_eating(t_philo *philo);
bool		isvalid_args(int argc, char **argv);
bool		init_info(t_info *info, char **data);
void		safe_print(char *s, t_philo *philo);
void		print_usage(void);

// time 
void		ft_usleep(size_t ms);
size_t		get_current_time(void);
size_t		get_current_timestamp(size_t start_time);

bool		init_philo(t_info *info, t_philo *philo, size_t id);
t_philo		*get_philo_by_pid(t_info *info, pid_t pid);
void		kill_all_philos(t_info *info, pid_t child_pid);

// sem utils
void		safe_sem_open(sem_t **sem, char *sem_name, unsigned int value);
void		safe_sem_wait(sem_t *sem, t_philo *philo);
void		safe_sem_post(sem_t *sem);
void		safe_sem_close(sem_t *sem);
void		safe_sem_unlinck(char *sem_name);
void		sem_clean(t_info *info);

// philo utils
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_routine(t_philo *philo);
void		*observe(void *data);

pid_t	safe_fork(void);
pid_t	sage_waitpid(int *status);

#endif
