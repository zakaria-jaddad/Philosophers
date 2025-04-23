SRC =	philo.c \
	src/ft_atoi.c src/parsing_utils.c src/time_utils.c ./src/print_utils.c ./src/check_death.c ./src/init_info.c \
	fprintf/ft_fprintf.c fprintf/ft_fprintf_put_unsigned_nbr_fd.c fprintf/ft_fprintf_putaddress_fd.c fprintf/ft_fprintf_putchar_fd.c fprintf/ft_fprintf_puthex_fd.c fprintf/ft_fprintf_putnbr_fd.c fprintf/ft_fprintf_putstr_fd.c fprintf/ft_fprintf_strlen.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra # -fsanitize=thread  # -g

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
