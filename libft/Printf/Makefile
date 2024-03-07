NAME = libftprintf.a
FLAGS = -Wall -Werror -Wextra

HEADER = .
SRCS = ft_printf.c ft_printf_utils.c ft_printf_hex.c

OBJECTS_FOLDER = ./obj/

OBJS = $(addprefix $(OBJECTS_FOLDER),$(SRCS:.c=.o))

all: $(OBJECTS_FOLDER) $(NAME)

$(OBJECTS_FOLDER):
	mkdir $(OBJECTS_FOLDER)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $?

$(OBJECTS_FOLDER)%.o: %.c
	@cc $(FLAGS) -c $< -o $@ -I $(HEADER)

clean:
	@rm -rf $(OBJECTS_FOLDER)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all