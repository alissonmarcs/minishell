CC			:= cc
NAME 		:= minishell
CFLAGS		:= -Wall -Werror -Wextra -g3 -O0
RFLAGS 		:= -lreadline -lhistory
BIN			:= ./bin/
HEADER		:= ./include/
SOURCE		:=	main.c tokenization.c token_list.c errors.c print_struct.c validations.c syntax.c command_list.c \
				populate_command_list.c debug.c echo_n.c expansion.c signals.c get_env.c quotes.c expansion_treatments.c \
				garbage.c pwd.c env.c cd.c execution.c exit.c export.c print_order.c unset.c pre_token_err.c \
				here_doc.c here_doc_vars.c here_doc_files.c here_doc_utils.c signal_cmd.c handle_redirect.c \
				handle_words.c handle_vars.c execution_utils.c pipes.c redirect.c builtins.c

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

$(BIN)%.o: ./src/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./src/tokenization/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./src/list/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./src/errors/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./src/signal/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./src/command_list/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./src/execution/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./src/get_env/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./src/debug/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./src/builtins/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(BIN)%.o: ./src/builtins/export/%.c $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $<...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(NAME): $(OBJECTS) $(HEADER)minishell.h
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@printf "$(BLUE)Compiling $(NAME)...$(END)\n"
	@printf "$(BLUE)-----------------------------------------------$(END)\n"
	@$(CC) $(CFLAGS) $(OBJECTS) $(42LIBS) -o $(NAME) $(RFLAGS)
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
	@printf "$(GREEN)All cleaned!$(END)\n"

re: fclean all

.PHONY: all clean fclean re
