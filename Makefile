CC			:= cc
NAME 		:= minishell
CFLAGS		:= -Wall -Werror -Wextra -g3 -O0
RFLAGS 		:= -lreadline -lhistory
BIN			:= ./bin/
HEADER		:= ./include/
SOURCE		:=	main.c token_list.c list_creation.c errors_1.c print_struct.c validations.c syntax.c command_list.c \
				populate_command_list.c debug.c echo_n.c expansion.c signals.c get_env.c quotes.c execution.c expansion_treatments.c \
				garbage.c
OBJECTS		:= $(addprefix $(BIN),$(SOURCE:.c=.o))
PRINTF		:= ./libft/Printf/libftprintf.a
LIBFT		:= ./libft/libft.a
42LIBS		:= $(PRINTF) $(LIBFT)

BLUE = \033[1;34m
RED=\033[0;31m
GREEN=\033[0;32m
END=\033[0m

all: $(42LIBS) $(BIN) $(NAME)

$(LIBFT):
	@printf "$(BLUE)---------------------$(END)\n"
	@printf "$(BLUE)--Compiling Libft...-$(END)\n"
	@printf "$(BLUE)---------------------$(END)\n"
	@make -C ./libft --no-print-directory

$(PRINTF):
	@printf "$(BLUE)---------------------$(END)\n"
	@printf "$(BLUE)-Compiling Printf...-$(END)\n"
	@printf "$(BLUE)---------------------$(END)\n"
	@make -C ./libft/Printf --no-print-directory

$(BIN):
	@mkdir -p $(BIN)

$(BIN)%.o: ./mandatory/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./mandatory/token/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./mandatory/list/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./mandatory/errors/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./mandatory/parsing/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./mandatory/command_list/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./mandatory/execution/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./mandatory/env/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./mandatory/debug/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./mandatory/built_in/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(NAME): $(OBJECTS) $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $(NAME)...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(RFLAGS) $(CFLAGS) $(OBJECTS) $(42LIBS) -o $(NAME)
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(GREEN)--$(NAME) compiled!-$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"

clean:
	@printf "$(RED)Cleaning...$(END)\n"
	@make -C ./libft/Printf clean --no-print-directory
	@make -C ./libft clean --no-print-directory
	@rm -rf $(BIN)

fclean: clean
	@printf "$(RED)Cleaning...$(END)\n"
	@make -C ./libft/Printf --no-print-directory fclean
	@make -C ./libft --no-print-directory fclean
	@rm -rf $(NAME)
	@rm -rf ./mandatory/log/log.txt
	@rm -rf $(NAME_BONUS)
	@printf "$(GREEN)All cleaned!$(END)\n"

re: fclean all

.PHONY: all clean fclean re