SRC =	philo_bonus.c \
	fprintf/ft_fprintf.c fprintf/ft_fprintf_strlen.c fprintf/ft_put_unsigned_nbr_fd.c fprintf/ft_putaddress_fd.c fprintf/ft_putchar_fd.c fprintf/ft_puthex_fd.c fprintf/ft_putnbr_fd.c fprintf/ft_putstr_fd.c \
	src/check_death.c src/check_done_eating.c src/ft_atoll.c src/ft_itoa.c src/ft_strcat.c src/ft_strcpy.c src/init_info.c src/init_philo.c src/parsing.c src/philo_utils_1.c src/philo_utils_2.c src/print_utils.c src/safe_fork.c src/sem_utils_1.c src/sem_utils_2.c src/time_utils.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra # -fsanitize=thread # -fsanitize=address -fsanitize=leak

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
