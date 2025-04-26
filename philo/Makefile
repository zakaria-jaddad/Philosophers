SRC =	philo.c \
	src/check_death.c src/ft_atoi.c src/init_forks.c src/init_info.c src/init_philo.c src/observer.c src/parsing_utils.c src/philo_eat.c src/philo_routine.c src/philo_sleep.c src/philo_think.c src/philo_utils.c src/print_utils.c src/start_philos.c src/time_utils.c\
	fprintf/ft_fprintf.c fprintf/ft_fprintf_put_unsigned_nbr_fd.c fprintf/ft_fprintf_putaddress_fd.c fprintf/ft_fprintf_putchar_fd.c fprintf/ft_fprintf_puthex_fd.c fprintf/ft_fprintf_putnbr_fd.c fprintf/ft_fprintf_putstr_fd.c fprintf/ft_fprintf_strlen.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

re: fclean all

clean: 
	rm -rf $(OBJ) $(OBJ:.o=.d)

fclean: clean
	rm -rf $(NAME) 

.PHONY: clean

-include $(OBJ:.o=.d)
