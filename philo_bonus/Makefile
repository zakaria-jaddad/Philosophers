SRC =	philo_bonus.c \
	src/ft_atoi.c src/ft_itoa.c src/ft_strcat.c src/ft_strcpy.c src/init_info.c src/init_philos.c src/parsing.c src/philo_eat.c src/philo_sleep.c src/philo_think.c src/philo_utils.c src/print_utils.c src/sem_utils.c src/time_utils.c ./src/philo_dine.c \
	fprintf/ft_fprintf.c fprintf/ft_fprintf_put_unsigned_nbr_fd.c fprintf/ft_fprintf_putaddress_fd.c fprintf/ft_fprintf_putchar_fd.c fprintf/ft_fprintf_puthex_fd.c fprintf/ft_fprintf_putnbr_fd.c fprintf/ft_fprintf_putstr_fd.c fprintf/ft_fprintf_strlen.c \


OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra # -g  -fsanitize=thread -fsanitize=address -fsanitize=leak

NAME = philo_bonus

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o  $@ -MMD

re: fclean all

clean: 
	rm -rf $(OBJ) $(OBJ:.o=.d)

fclean: clean
	rm -rf $(NAME) 

.PHONY: clean

-include $(OBJ:.o=.d)
