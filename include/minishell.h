/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:34:40 by matesant          #+#    #+#             */
/*   Updated: 2024/03/08 18:00:58 by matesant         ###   ########.fr       */
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

# define PROMPT "\001\e[0m\002\e[33mCarlitoShell$ \001\e[0m\002"

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
}					t_minishell;

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

/*------------------------------------TOKEN--------------------------------*/
//#Validation pre-tokenization
void				ft_open_quotes(char *str);
void				ft_skip_quotes(char *str, unsigned long *i);

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

#endif