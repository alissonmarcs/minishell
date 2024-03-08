NAME = libft.a
FLAGS = -Wall -Werror -Wextra -g3 -O0

HEADER = .
SRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_memset.c ft_strlen.c \
	ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcat.c \
	ft_strlcpy.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
	ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
	ft_substr.c ft_putchar_fd.c ft_putstr_fd.c ft_strjoin.c\
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	ft_striteri.c ft_putendl_fd.c ft_putnbr_fd.c ft_delete_matrice.c \
	ft_issignal.c ft_atol.c ft_abs.c get_next_line.c get_next_line_utils.c \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
	ft_lstmap_bonus.c ft_isspace.c

OBJECTS_FOLDER = ./obj/

OBJS = $(addprefix $(OBJECTS_FOLDER),$(SRCS:.c=.o))

all: $(OBJECTS_FOLDER) $(NAME)

$(OBJECTS_FOLDER):
	@mkdir $(OBJECTS_FOLDER)

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
