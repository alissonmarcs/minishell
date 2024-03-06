NAME = libftprintf.a
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -rf

HEADER = .
SRCS = ft_printf.c ft_printf_utils.c ft_printf_hex.c
OBJS =  $(SRCS:.c=.o)

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $?

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@ -I $(HEADER)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all