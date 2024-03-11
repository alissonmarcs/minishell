/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:34:40 by matesant          #+#    #+#             */
/*   Updated: 2024/03/08 19:12:45 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>

# define PROMPT "\001\e[0m\002\e[33mCarlitoShell$ \001\e[0m\002"

typedef struct s_command
{
	char				*name;
	char				**argv;
	int					tube[2];
	bool				output_to_pipe;
	struct s_command	*prev;
	struct s_command	*next;
}					t_command;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_minishell
{
	char			*user_input;
	t_token			*tokens;
	t_command		*commands;
}					t_minishell;

typedef enum e_bool
{
	FALSE,
	TRUE
}t_bool;

enum				e_token
{
	SPACES = 1,
	VAR,
	WORD,
	PIPE,
	INPUT,
	TRUNC,
	APPEND,
	HERE_DOC,
	END
};

t_minishell			*ft_get_shell(void);

/*------------------------------------TOKEN--------------------------------*/
//#Validation pre-tokenization
t_bool				ft_open_quotes(char *str);
void				ft_skip_quotes(char *str, unsigned long *i);
t_bool				ft_double_separators(char *line);

//#Tokenization
void				ft_tokenize(t_minishell *shell);
void				ft_clear_spaces(char **str);
/*------------------------------------------------------------------------*/

/*------------------------------------PARSER-------------------------------*/
void				ft_check_syntax(t_token *tokens);
/*------------------------------------------------------------------------*/

/*------------------------------------EXIT--------------------------------*/
void				ft_error(char *str);
void				ft_lstend(t_token **tokens, char *str, int type);
/*------------------------------------------------------------------------*/

/*------------------------------------LIST--------------------------------*/
t_token				*ft_create_list(char *str, int type);
void				ft_free_list(t_minishell *shell);
/*------------------------------------------------------------------------*/

/*---------------------------------DEBUGGING------------------------------*/
void				ft_print_stack(t_token *stack);
/*------------------------------------------------------------------------*/

t_command 			*new_command(char *name, bool pipe);
void				append_command(t_command **cmd_list, t_command *new);
void				print_cmd_list(t_command *list);

#endif