/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:34:40 by matesant          #+#    #+#             */
/*   Updated: 2024/03/13 17:57:25 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "defines.h"
# include "types.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*----------------------------------MAIN-STRUCT----------------------------*/
t_minishell	*ft_get_shell(void);
/*-------------------------------------------------------------------------*/

/*------------------------------------TOKEN--------------------------------*/
//#Validation pre-tokenization
t_bool		ft_open_quotes(char *str);
void		ft_skip_quotes(char *str, unsigned long *i);
t_bool		ft_double_separators(char *line);
t_bool		ft_var_expansion(char **line);

//#Tokenization
int			ft_is_separator(char *str);
t_bool		ft_tokenize(t_minishell *shell);
void		ft_clear_spaces(char **str);
char		*ft_check_syntax(t_token *tokens);
/*-------------------------------------------------------------------------*/

/*------------------------------------PARSER-------------------------------*/
void		append_command(t_command **cmd_list, t_command *new);
t_command	*new_command(char *name, bool pipe);
void		free_cmd_list(t_command **cmd_list);
t_command	*get_last_command(t_command *cmd);
int			get_len_args(t_token *token);
void		add_dummy_node(t_command **cmd);
void		populate_command_list(t_minishell *minishell);
void		get_args(t_token **token, t_command *last);
void		handle_words(t_token **token, t_command **cmd);
void		handle_pipe(t_token **token, t_command **cmd);
void		handle_truc(t_token **token, t_command *cmd);
void		free_io(t_io *io);
/*------------------------------------------------------------------------*/

/*------------------------------------EXIT--------------------------------*/
t_bool		ft_error(char *str);
void		ft_lstend(t_token **tokens, char *str, int type);
/*------------------------------------------------------------------------*/

/*------------------------------------LIST--------------------------------*/
t_token		*ft_create_list(char *str, int type);
void		ft_free_list(t_minishell *shell);
/*------------------------------------------------------------------------*/

/*---------------------------------DEBUGGING------------------------------*/
void		ft_print_stack(t_token *stack);
void		print_cmd_list(t_command *list);
/*------------------------------------------------------------------------*/

/*----------------------------------BUILT-IN------------------------------*/
void		ft_tony_tony_chopper(void);
void				append_command(t_command **cmd_list, t_command *new);
t_command 			*new_command(char *name, bool pipe);
void				print_cmd_list(t_command *list);
void				free_cmd_list(t_command **cmd_list);
t_command			*get_last_command(t_command *cmd);
int					get_len_args(t_token *token);
void				add_dummy_node(t_command **cmd);
void				populate_command_list(t_minishell *minishell);
void				get_args(t_token **token, t_command *last);
void				handle_words(t_token **token, t_command **cmd);
void				handle_pipe(t_token **token, t_command **cmd);
void				handle_truc_input(t_token **token, t_command *cmd);
void				free_io(t_io *io);
void				set_commands_with_no_argv(t_command *cmd);

/*------------------------------------------------------------------------*/

/*---------------------------------EXECUTION------------------------------*/
/*------------------------------------------------------------------------*/
#endif