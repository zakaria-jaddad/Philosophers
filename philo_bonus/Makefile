SRC =	philo_bonus.c \
	src/isvalid_number.c \
	src/ft_atoll.c \
	src/ft_itoa.c \
	src/ft_strcpy.c \
	src/ft_strcat.c \
	utils/fprintf/ft_fprintf.c utils/fprintf/ft_putaddress_fd.c utils/fprintf/ft_putchar_fd.c utils/fprintf/ft_puthex_fd.c utils/fprintf/ft_putnbr_fd.c utils/fprintf/ft_putstr_fd.c utils/fprintf/ft_put_unsigned_nbr_fd.c utils/fprintf/ft_fprintf_strlen.c


OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread # -fsanitize=address -fsanitize=leak

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
