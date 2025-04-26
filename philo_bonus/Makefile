SRC =	philo_bonus.c \
	src/isvalid_number.c \
	src/ft_atoll.c \
	src/ft_itoa.c \
	src/ft_strcpy.c \
	src/ft_strcat.c \
	fprintf/ft_fprintf.c fprintf/ft_fprintf_put_unsigned_nbr_fd.c fprintf/ft_fprintf_putaddress_fd.c fprintf/ft_fprintf_putchar_fd.c fprintf/ft_fprintf_puthex_fd.c fprintf/ft_fprintf_putnbr_fd.c fprintf/ft_fprintf_putstr_fd.c fprintf/ft_fprintf_strlen.c \


OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra # -fsanitize=thread -fsanitize=address -fsanitize=leak

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
