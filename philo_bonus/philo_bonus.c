#include "./philo_bonus.h"

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
bool check_death(t_philo *philo)
{
        bool dead;
	if (sem_wait(philo->dead_lock) != 0) {
		ft_fprintf(STDERR_FILENO, "ERROR: Locking Semaphore\n");
		exit(EXIT_FAILURE);
        }
        dead = philo->dead;
	if (sem_post(philo->dead_lock) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Unlocking Semaphore\n");
		exit(EXIT_FAILURE);
	}
        return dead;
}

void	safe_sem_open(sem_t **sem, char *sem_name, unsigned int value)
{
	// The S_IRUSR and S_IWUSR permit semaphore read and write for the user
	// O_EXCL if semaphore already exist return an error
	sem_unlink(sem_name);
	*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0677, value);
	if (*sem == SEM_FAILED)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Semaphore Initialization\n");
		exit(EXIT_FAILURE);
	}
}

void	safe_sem_wait(sem_t *sem, t_philo *philo)
{
        if (check_death(philo) == true)
                return ;
	if (sem_wait(sem) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Locking Semaphore\n");
		exit(EXIT_FAILURE);
	}
}
void	safe_sem_post(sem_t *sem)
{
	if (sem_post(sem) != 0)
	{
		ft_fprintf(STDERR_FILENO, "ERROR: Unlocking Semaphore\n");
		exit(EXIT_FAILURE);
	}
}

void safe_sem_close(sem_t *sem)
{
        if (sem_close(sem) != 0) {
                ft_fprintf(STDERR_FILENO, "ERROR Semaphore Closing\n");
                exit(EXIT_FAILURE);
        }
}


void safe_sem_unlinck(char *sem_name)
{
        if (sem_unlink(sem_name) != 0) {
                ft_fprintf(STDERR_FILENO, "ERROR Semaphore Closing\n");
                exit(EXIT_FAILURE);
        }
}

bool check_done_eating(t_philo *philo)
{
        bool done ;

        safe_sem_wait(philo->done_eating_lock, philo);
        done = philo->done_eating;
        safe_sem_post(philo->done_eating_lock);
        return done;
}

void	safe_print(char *s, t_philo *philo)
{
	// check death flag firs
	safe_sem_wait(philo->dead_lock, philo);
	if (philo->dead == true)
		return ;
	sem_post(philo->dead_lock);

	// lock print lock
	safe_sem_wait(philo->print_lock, philo);
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
		|| info->num_times_to_eat < 1)
		return (false);

	// semaphore initialization
	safe_sem_open(&info->forks, "forks", info->num_of_philos);
	safe_sem_open(&info->print_lock, "print_lock", 1);
	return (true);
}

// Improved version of sleep function
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
bool	init_philo(t_info *info, t_philo *philo, size_t id)
{

	philo->id = id;
	philo->meals_eaten = 0;
	philo->num_times_to_eat = info->num_times_to_eat;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->time_to_die = info->time_to_die;
	(void)!(philo->is_sleeping = philo->done_eating = philo->is_eating = false);
	philo->dead = false;

	// get_current_time return -1 when fail
	philo->last_meal_time = get_current_time();
	philo->start_time = get_current_time();
	philo->forks = info->forks;
	philo->print_lock = info->print_lock;

        return true;
}

void create_semaphores(t_philo *philo)
{
	
        char sem_name[100];
        char strphilo_id[5];

        memset(sem_name, 0, sizeof(sem_name));
        memset(strphilo_id, 0, sizeof(strphilo_id));

        char *_strphilo_id;

        _strphilo_id  = ft_itoa(philo->id);
        if (_strphilo_id == NULL)
                return ;

        // copy philo id to stack
        ft_strcpy(strphilo_id, _strphilo_id);

        // free heap philo id
        _strphilo_id = (free(_strphilo_id), NULL);

	// initialization of is_eating_lock and done_eating_lock;
	// each philo should have a semaphore sared only with the observer

        // copy name to sem_name
        ft_strcpy(sem_name, "is_eating_lock_") ;

        // add philo id to semaphore name
        ft_strcat(sem_name, strphilo_id);
        philo->is_eating_sem_name = sem_name;
	safe_sem_open(&philo->is_eating_lock, sem_name, 1);

        // copy name to sem_name
        ft_strcpy(sem_name, "done_eating_lock_") ;

        // add philo id to semaphore name
        ft_strcat(sem_name, strphilo_id);
        philo->done_eating_sem_name = sem_name;
	safe_sem_open(&philo->done_eating_lock, sem_name, 1);

        // copy name to sem_name
        ft_strcpy(sem_name, "dead_lock_") ;

        // add philo id to semaphore name
        ft_strcat(sem_name, strphilo_id);
        philo->dead_sem_name = sem_name;
	safe_sem_open(&philo->dead_lock, sem_name, 1);
}

void	philo_eat(t_philo *philo)
{
	// first fork
	safe_sem_wait(philo->forks, philo);
	safe_print("%zu %d has taken a fork\n", philo);

	// second fork
	safe_sem_wait(philo->forks, philo);
	safe_print("%zu %d has taken a fork\n", philo);

	safe_print("%zu %d is eating\n", philo);

	// lock is_eating_lock to update eating values
	safe_sem_wait(philo->is_eating_lock, philo);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	safe_sem_post(philo->is_eating_lock);

	ft_usleep(philo->time_to_eat);

	// unlock forks
	safe_sem_post(philo->forks);
	safe_sem_post(philo->forks);
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

void	philo_routine(t_philo *philo)
{
        if (philo->id % 2 == 0) 
                usleep(500);
	while (true)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (philo->meals_eaten == philo->num_times_to_eat)
		{
			// lock done_eating_lock
			safe_sem_wait(philo->done_eating_lock, philo);
			// update done eating
			philo->done_eating = true;
			// unlock done_eating_lock
			safe_sem_post(philo->done_eating_lock);
			break ;
		}
                if (check_death(philo) == true) {
                        break ;
                }
	}
}

void	*observe(void *data)
{
	t_philo	*philo;
	ssize_t	time_difference;

        philo = (t_philo *) data;
        while (true) 
        {
                if (check_done_eating(philo) == true)
			exit(EXIT_SUCCESS);
                        

                // check time_difference
                safe_sem_wait(philo->is_eating_lock, philo);
                time_difference = get_current_time() - philo->last_meal_time;
                safe_sem_post(philo->is_eating_lock);

                if (time_difference > philo->time_to_die && check_done_eating(philo) == false)
                {
			safe_print("%zu %d died\n", philo);

                        // lock print semaphore
                        /* safe_sem_wait(philo->print_lock, philo); */

                        safe_sem_wait(philo->dead_lock, philo);
                        philo->dead = true;
                        safe_sem_post(philo->dead_lock);

			// philo died
                        exit(EXIT_FAILURE);
                }
        }
	return (NULL);
}

t_philo *get_philo_by_pid(t_info *info, pid_t pid) {

        int i;

        i = 0;
        while (i < info->num_of_philos) {
                if (info->philos[i].pid == pid) 
                        return (&info->philos[i]);
                i++;
        }
        return (NULL);
}

void kill_all_philos(t_info *info, pid_t child_pid)
{

        for (ssize_t i = 0; i < info->num_of_philos; i++) {
                if (info->philos[i].pid == child_pid || info->philos[i].done_eating == true)
                        continue ;
                if (kill(info->philos[i].pid, SIGSTOP) == -1) {
                        ft_fprintf(STDERR_FILENO, "ERROR: Kill\n");
                        exit(EXIT_FAILURE);
                }
        }
}

void sem_clean(t_info *info)
{
        t_philo *philo;

        for (ssize_t i = 0; i < info->num_of_philos; i++) {

                philo = &info->philos[i];

                // Each philos has it's own semaphore
                
                // clean and unlink dead_lock semaphore
                safe_sem_close(philo->dead_lock);
                safe_sem_unlinck(philo->dead_sem_name);

                // clean and unlink is_eating semaphore
                safe_sem_close(philo->is_eating_lock);
                safe_sem_unlinck(philo->is_eating_sem_name);

                // clean and unlink done_eating semaphore
                safe_sem_close(philo->done_eating_lock);
                safe_sem_unlinck(philo->done_eating_sem_name);
        }

        // clean and unlink forks 
        safe_sem_close(info->forks);
        safe_sem_unlinck("forks");

        // clean and unlink print_lock 
        safe_sem_close(info->print_lock);
        safe_sem_unlinck("print_lock");

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

	for (ssize_t i = 0; i < info.num_of_philos; i++)
	{
		pid = fork();
                if (pid < 0) 
                {
                        ft_fprintf(2, "ERROR: Process Creation");
                        exit(EXIT_FAILURE);
                }
                if (pid == 0)
		{
                        pthread_t observer;
                        t_philo *philo = &info.philos[i];

			info.philos[i].pid = getpid();
		        // TODO: create philo semaphores
			create_semaphores(philo);

                        // each process should have a philo thread and an observer thread
                        // observer determine weather a philo 
                        //      -> Finished eating
                        //      -> died
                        // Obsserver Thread Creation
                        if (pthread_create(&observer, NULL, observe, philo) != 0) {
                                ft_fprintf(STDERR_FILENO, "ERROR: Thread Creation");
                                exit(EXIT_FAILURE);
                        }

                        // detach observer
                        if (pthread_detach(observer) != 0) {
                                ft_fprintf(STDERR_FILENO, "ERROR: Thread Detaching");
                                exit(EXIT_FAILURE);
                        }

                        // philo routine
                        philo_routine(philo);

                        // check done eating
                        if (check_done_eating(philo) == true)
			        exit(EXIT_SUCCESS);
                        
                        exit(EXIT_SUCCESS);
                }
                else
                        info.philos[i].pid = pid;
	}


        for (ssize_t i = 0; i < info.num_of_philos; i++) {
                pid_t child_pid = waitpid(-1, &status, 0);
                if (child_pid == -1)
                {
                        ft_fprintf(STDERR_FILENO, "ERROR: Waitpid\n");
                        exit(EXIT_FAILURE);
                }

                // set philo as done eating
                if (WEXITSTATUS(status) == EXIT_SUCCESS) {
                        t_philo *philo = get_philo_by_pid(&info, child_pid);
                        if (philo == NULL)
                                break ;
                        philo->done_eating = true;
                        continue ;
                }

                // if philo DIED
                if (WEXITSTATUS(status) == EXIT_FAILURE)
                {
                        // lock global semaphores
                        kill_all_philos(&info, child_pid);
                        break ;
                }

                // TODO: destroy and unlink all semaphores
                sem_clean(&info);
        }
	return (EXIT_SUCCESS);
}

