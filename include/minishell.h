/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:34:40 by matesant          #+#    #+#             */
/*   Updated: 2024/03/20 18:18:45 by matesant         ###   ########.fr       */
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
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>

/*----------------------------------MAIN-STRUCT----------------------------*/
t_minishell	*ft_get_shell(void);
/*-------------------------------------------------------------------------*/

/*------------------------------------TOKEN--------------------------------*/
//#Validation pre-tokenization
t_bool		ft_open_quotes(char *str);
void		ft_skip_quotes(char *str, unsigned long *i);
t_bool		ft_forbidden_separators(char *line);
t_bool		ft_only_spaces(char *line);
t_bool		ft_var_expansion(void);

//#Tokenization
int			ft_is_separator(char *str);
t_bool		ft_tokenize(t_minishell *shell);
void		ft_clear_spaces(char **str);
char		*ft_check_syntax(t_token *tokens);
void		ft_quotes_treatment(char **str);
char		*ft_getenv(char *env);
void		ft_clone_env(t_minishell *shell);
void		ft_remove_quotes(void);
/*-------------------------------------------------------------------------*/

/*------------------------------------PARSER-------------------------------*/
void		append_command(t_command **cmd_list, t_command *new);
t_command	*new_command(char *name, t_bool pipe);
void		print_cmd_list(t_command *list);
void		free_cmd_list(t_command **cmd_list);
t_command	*get_last_command(t_command *cmd);
int			get_len_args(t_token *token);
void		add_dummy_node(t_command **cmd);
void		populate_command_list(t_minishell *minishell);
void		get_args(t_token **tokens, t_command *last);
void		handle_words(t_token **token, t_command **cmd);
void		handle_pipe(t_token **token, t_command **cmd);
void		handle_trunc_append_input(t_token **token, t_command *cmd);
void		free_io(t_io *io);
void		set_commands_with_no_argv(t_command *cmd);
void		ft_get_env(t_minishell *shell);
void		create_argv(t_token **tokens, t_command *last);
void		add_to_argv(t_token **tokens, t_command *last);
int			array_len(char **array);
void		open_output_file(t_token *tokens, t_command *last);
void		open_input_file(t_token *tokens, t_command *last);
void		get_standard_fds(t_minishell *shell);

/*------------------------------------------------------------------------*/

/*------------------------------------EXIT--------------------------------*/
t_bool		ft_error(char *str);
void		ft_lstend(t_token **tokens, char *str, int type);
void		ft_free(void **ptr);
/*------------------------------------------------------------------------*/

/*------------------------------------LIST--------------------------------*/
t_token		*ft_create_list(char *str, int type);
void		ft_free_tokens(t_minishell *shell);
void		ft_free_env(t_minishell *shell);
/*------------------------------------------------------------------------*/

/*---------------------------------DEBUGGING------------------------------*/
void		ft_print_stack(t_token *stack);
void		print_cmd_list(t_command *list);
void		ft_print_env_list(t_env *env_list);
/*------------------------------------------------------------------------*/

/*----------------------------------BUILT-IN------------------------------*/
void		ft_echo_builtin(char **argv);

/*------------------------------------------------------------------------*/

/*----------------------------------SIGNALS-------------------------------*/
void		ft_receive_signal(void);
t_bool		ft_handle_cntl_c(int sig);
/*------------------------------------------------------------------------*/

/*---------------------------------EXECUTION------------------------------*/
void		create_pipes(t_command *cmds);
t_bool		check_redirect_files(t_command *cmd);
void		set_pipes(t_command *cmd);

/*------------------------------------------------------------------------*/
#endif