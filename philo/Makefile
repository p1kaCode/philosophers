NAME = philo

SRCS =	utils/ft_atoi.c \
		src/philo.c 

OBJS = $(SRCS:.c=.o)

HDRS = philo.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

%.o : %.c $(HDRS) Makefile
	$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re