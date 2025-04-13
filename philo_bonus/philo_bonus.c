#include "./philo_bonus.h"
#include "utils/fprintf/ft_fprintf.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

ssize_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_fprintf(STDERR_FILENO, "ERROR: gettimeofday\n"), -1);
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

void	safe_sem_open(sem_t *sem, char *sem_name, unsigned int value)
{
	// The S_IRUSR and S_IWUSR permit semaphore read and write for the user
	// O_EXCL if semaphore already exist return an error
	sem_unlink(sem_name);
	sem = sem_open(sem_name, O_CREAT, 0677, value);
        printf("sem_name = %s\n", sem_name);
        printf("sem = %p\n", sem);
	if (sem == SEM_FAILED)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: semaphore initialization\n");
		exit(EXIT_FAILURE);
	}
}

void	safe_sem_wait(sem_t *sem)
{
	if (sem_wait(sem) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: locking semaphore\n");
		exit(EXIT_FAILURE);
	}
}
void	safe_sem_post(sem_t *sem)
{
	if (sem_post(sem) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: unlocking semaphore\n");
		exit(EXIT_FAILURE);
	}
}

void	safe_print(char *s, t_philo *philo)
{
	// check death flag firs
	safe_sem_wait(philo->dead_lock);
	if (*philo->dead == true)
		return ;
	sem_post(philo->dead_lock);
	// lock print lock
	safe_sem_wait(philo->print_lock);
	printf(s, get_current_timestamp(philo->start_time), philo->id);
	safe_sem_post(philo->print_lock);
}

bool	init_info(t_info *info, char **data)
{
	info->death_flag = false;
	info->num_of_philos = ft_atoi(data[0]);
	if (info->num_of_philos > 200)
		return (false);
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
	// semaphore initialization
	safe_sem_open(info->forks, "forks", info->num_of_philos);
        printf("info->forks = %p\n", info->forks);
        return false;
	safe_sem_open(info->print_lock, "print_lock", 1);
	safe_sem_open(info->dead_lock, "dead_lock", 1);
	return (true);
}

bool	init_philo(t_info *info, t_philo *philo, size_t id)
{
        char sem_name[100];
        char strphilo_id[5];

        memset(sem_name, 0, sizeof(sem_name));
        memset(strphilo_id, 0, sizeof(strphilo_id));

        char *_strphilo_id;

        _strphilo_id  = ft_itoa(id);
        if (_strphilo_id == NULL)
                return false;

        // copy philo id to stack
        ft_strcpy(strphilo_id, _strphilo_id);

        // free heap philo id
        _strphilo_id = (free(_strphilo_id), NULL);

	philo->id = id;
	philo->meals_eaten = 0;
	philo->num_times_to_eat = info->num_times_to_eat;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->time_to_die = info->time_to_die;
	(void)!(philo->is_sleeping = philo->done_eating = philo->is_eating = false);
	philo->dead = &info->death_flag;
	// get_current_time return -1 when fail
	philo->last_meal_time = get_current_time();
	philo->start_time = get_current_time();
	philo->forks = info->forks;
	philo->print_lock = info->print_lock;
	philo->dead_lock = info->dead_lock;

	// initialization of is_eating_lock and done_eating_lock;
	// each philo should have a semaphore sared only with the observer

        // copy name to sem_name
        ft_strcpy(sem_name, "is_eating_lock_") ;

        // add philo id to semaphore name
        ft_strcat(sem_name, strphilo_id);
	safe_sem_open(philo->is_eating_lock, sem_name, 1);

        // copy name to sem_name
        ft_strcpy(sem_name, "done_eating_lock_") ;

        // add philo id to semaphore name
        ft_strcat(sem_name, strphilo_id);
	safe_sem_open(philo->done_eating_lock, sem_name, 1);
        return true;
}

void	philo_eat(t_philo *philo)
{
	// first fork
	safe_sem_wait(philo->forks);
	safe_print("%zu %d has taken a fork\n", philo);
	// second fork
	safe_sem_wait(philo->forks);
	safe_print("%zu %d has taken a fork\n", philo);
	safe_print("%zu %d is eating\n", philo);
	// lock is_eating_lock to update eating values
	safe_sem_wait(philo->is_eating_lock);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	safe_sem_post(philo->is_eating_lock);
	usleep(philo->time_to_eat * 1000);
	// unlock forks
	safe_sem_post(philo->forks);
	safe_sem_post(philo->forks);
}

void	philo_sleep(t_philo *philo)
{
	safe_print("%zu %d is sleeping\n", philo);
	usleep(philo->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	safe_print("%zu %d is thinking\n", philo);
}

void	philo_routine(t_philo *philo)
{
	while (true)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (philo->meals_eaten == philo->num_times_to_eat)
		{
			// lock done_eating_lock
			safe_sem_wait(philo->done_eating_lock);
			// update done eating
			philo->done_eating = true;
			// unlock done_eating_lock
			safe_sem_post(philo->done_eating_lock);
			break ;
		}
	}
}

int	main(int argc, char **argv)
{
	t_info	info;
	pid_t	pid;
	int		status;

	if (isvalid_args(--argc, ++argv) == false)
		return (print_usage(), EXIT_FAILURE);
	if (init_info(&info, argv) == false)
		return (print_usage(), EXIT_FAILURE);
	for (ssize_t i = 0; i < info.num_of_philos; i++)
		init_philo(&info, &info.philos[i], i + 1);
        printf("info.philos[0].forks = %p\n", info.philos[0].forks);
        printf("info.forks = %p\n", info.forks);
        return 0;
	for (ssize_t i = 0; i < info.num_of_philos; i++)
	{
		// create a process aka philosopher
		pid = fork();
		// TODO: child routine of philo
		if (pid == 0)
		{
			info.philos[i].pid = getpid();
			philo_routine(&info.philos[i]);
			return (EXIT_FAILURE);
		}
	}
	// Parent process should wait for children
	wait(&status);
	printf("This is the parent process id: %d, this is the state of the last child process %s\n", getpid(),
		(WIFEXITED(status) != 0) ? "true" : "false");
	return (EXIT_SUCCESS);
}
