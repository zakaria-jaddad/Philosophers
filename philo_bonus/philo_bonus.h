/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:05:27 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/29 00:28:38 by zajaddad         ###   ########.fr       */
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
# define PHILO_DIED 42
# define PHILO_DONE_EATING 1337

typedef struct s_philo
{
	pid_t	pid;
	int		id;
	bool	is_sleeping;
	size_t	meals_eaten;
	size_t	num_times_to_eat;
	ssize_t	last_meal_time;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	start_time;

	sem_t	*dead_lock;
	bool	dead;

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

ssize_t		ft_atoi(const char *str);
char		*ft_itoa(int n);
char		*ft_strcpy(char *s1, char *s2);
void		ft_strcat(char *des, const char *src);

// info utils
bool		init_info(t_info *info, char **data);
void		init_philos(t_info *info);

// parsing
bool		isvalid_args(int argc, char **argv);
bool		isvalid_number(char *element);

// time utils
ssize_t		get_current_time(void);
ssize_t		get_current_timestamp(ssize_t start_time);
int			ft_usleep(size_t milliseconds);

// sem utils
void		safe_sem_open(sem_t **sem, char *sem_name, unsigned int value);
void		safe_sem_wait(sem_t *sem, t_philo *philo);
void		safe_sem_post(sem_t *sem);
void		safe_sem_close(sem_t *sem);
void		safe_sem_unlink(char *sem_name);

// philo utils
bool		check_philo_death(t_philo *philo);
bool		philo_done_eating(t_philo *philo);
void		kill_all_philos(t_info *info, pid_t child_pid);
t_philo		*get_philo_by_pid(t_info *info, pid_t pid);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_dine(t_philo *philo);

// print utils
void		print_usage(void);
void		safe_print(char *s, t_philo *philo);
#endif
