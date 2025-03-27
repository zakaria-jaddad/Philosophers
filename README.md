# PHILOSOPHERS

Things need to know

- One or more Philos sit at a round table
- The Philos either **eat, Think or sleep**
- There are forks on the table, number of forks is equivalent
  To number of Philos
- Each Philo has two forks one on his right and the other one on his left
- Once a Philo stop eating they put the two forks back to the table
- After eating a Philo start sleeping, Once awake they start thinking
- The process of Philosophing stops when a Philo dies

The program should take the following arguments.

- number of philosophers
- time to die _in milliseconds_
- time to eat _in milliseconds_
- time to sleep _in milliseconds_

Each Philo has a number from 1 to number of philosophers

A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher

## Threads

Each Thread has it's own contexts, it's own id, stack, pointers, registers
But all Threads share the same virtual memory (heap), shared libraries and the same open fds.

Threads don't have the same parent-child hierarchy that processes do.
A thread can creat other threads to form a group.

Any thread can wait for other threads to complete, or kill any of other threads

Since all threads share the same memory, any thread can write and read to the same memory,
which makes communicaation between threads much easier.

Thread operations include thread creation, termination, synchronization (joins,blocking), scheduling, data management and process interaction.
A thread does not maintain a list of created threads, nor does it know the thread that created it.
All threads within a process share the same address space.
Threads in the same process share:

- Process instructions
- Most data
- open files (descriptors)
- signals and signal handlers
- current working directory
- User and group id
- Each thread has a unique:

Thread ID

- set of registers, stack pointer
- stack for local variables, return addresses
- signal mask
- priority
- Return value: errno
- pthread functions return "0" if OK.

### Creating a Thread

The `ptread_creat` function is used in order to creat a new thread

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
```

- `thread`: a pointer to the `pthread_t` variable, to store the value of
  the ID we want to creat.
- `attr`: thread can be created with attributes specified by `attr`, wither a process, if attr is `NULL` the default attributes are used.
- The tread created start executing from the `start_routine` function with `args` as it own arguments

- `arg`: a pointer towards an argument to pass to the thread’s start_routine function. If we’d like to pass several parameters to this function,
  we will need to give it a pointer to a data structure.

If the `start_routine` returns, the effect is as if there was an implicit call to `pthread_exit`, (the created tread finished),
using there return value of the `start_routine` as it's exit status.

The `thread` variable in _MacOS_ pointe to a struct with different attributes, but in _Linux_ the `pthread_t` is just a
re definition of `long int`

```c

// MacOS
struct _opaque_pthread_t {
	long __sig;                                             // Signal number
	struct __darwin_pthread_handler_rec  *__cleanup_stack;  // Pointer to __darwin_pthread_handler_rec object
	char __opaque[__PTHREAD_SIZE__];                        // Array of Bytes for storing data about the current thread
};
typedef struct _opaque_pthread_t *__darwin_pthread_t;
typedef __darwin_pthread_t pthread_t;

// Linux
typedef unsigned long int pthread_t;

```

```c
struct __darwin_pthread_handler_rec {
	void (*__routine)(void *);	// Routine to call
	void *__arg;			    // Argument to pass
	struct __darwin_pthread_handler_rec *__next;
};
```

The `pthread_join` function suspends execution of the calling thread until the target thread terminates unless the target thread has already terminated.

```c
int pthread_join(pthread_t thread, void **value_ptr);
```

This is the MacOS definition,
The `pthread_join` accept 2 arguments

- `thread` object of `pthread_t`
- `value_ptr` if not NULL value is used to terminate the tread calling `pthread_exit`.

On return from a successful `pthread_join()` call with a non-NULL value_ptr argument, the value passed to `pthread_exit()` by the terminating thread is
stored in the location referenced by value_ptr.

## Mutexes:

Mutexes are used to prevent data inconsistencies due to race conditions.
A race condition often occurs when two or more threads need to perform operations on the same memory area, but the results of computations depends on the order in which these operations are performed.

Mutexes are used for serializing shared resources.
Anytime a global resource is accessed by more than one thread the resource should have a Mutex associated with it.
One can apply a mutex to protect a segment of memory ("critical region") from other threads.

Mutexes can be applied only to threads in a single process and do not work between processes as do semaphores.

When a mutex lock is attempted against a mutex which is held by another thread, the thread is blocked until the mutex is unlocked.
When a thread terminates, the mutex does not unless explicitly unlocked.
Nothing happens by default.

The `pthread_mutex_lock()` function locks mutex.
If the mutex is already locked, the calling thread will block until the mutex becomes available.

```c
int pthread_mutex_lock(pthread_mutex_t *mutex);
```

If the current thread holds the lock on mutex, then the `pthread_mutex_unlock()` function unlocks mutex.

Calling `pthread_mutex_unlock()` with a mutex that the calling thread does not hold will result in undefined behavior.

```c
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

## Joins

A join is performed when one wants to wait for a thread to finish.

A thread calling routine may launch multiple threads then wait for them to finish to get the results.

One wait for the completion of the threads with a join.

## Problem Walkthrough

### Input Validation

The Philo program needs 4 or 5 arguments

```bash
./philo [number_of_philosophers] [time_to_die_in_milliseconds] [stime_to_eat_in_milliseconds] [time_to_sleep_in_milliseconds] [Optional : Number_of_times_all_the_philosophers_need_to_eat]
```

- Check if the input is a digit Input
- Convert The input to Integer

### Struct Information

```c
typedef struct s_philo
{
	pthread_t		thread;             // Philo thread information
	int				id;                 // Philo ID
	bool			is_eating;          //
	int				meals_eaten;        // Number of meals eaten
	size_t			last_meal;          // Time When philo ate his last meal
	size_t			time_to_die;        //
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;         //
	int				num_of_philos;      // Total number of Philos
	int				num_times_to_eat;   // Number of Times To eat
    bool			*dead;              // Pointer to death flag ditermin if a philo died
	pthread_mutex_t	*r_fork;            // Philo right fork
	pthread_mutex_t	*l_fork;            // Philo left fork
	pthread_mutex_t	*write_lock;        //
	pthread_mutex_t	*dead_lock;         //
	pthread_mutex_t	*meal_lock;         //
}					t_philo;

typedef struct s_program
{
	bool            dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;        // array of current philos
}					t_program;
```
