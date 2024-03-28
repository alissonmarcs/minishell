/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_command_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:03:30 by almarcos          #+#    #+#             */
/*   Updated: 2024/03/26 16:47:48 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_dummy_node(t_command **cmd)
{
	t_command	*dummy;

	dummy = new_command(NULL, FALSE);
	append_command(cmd, dummy);
}

void	populate_command_list(t_minishell *shell)
{
	t_token		*token;
	t_command	*command;

	token = shell->tokens;
	command = shell->commands;
	add_dummy_node(&command);
	while (token)
	{
		if (token->type == WORD)
			handle_words(&token, &command);
		else if (token->type == PIPE)
			handle_pipe(&token, &command);
		else if (token->type == TRUNC || token->type == APPEND
			|| token->type == INPUT)
			handle_trunc_append_input(&token, command);
		else if (token->type == VAR)
			handle_vars(&token, &command);
		else if (token->type == END)
			break ;
	}
	set_commands_with_no_argv(command);
	shell->commands = command;
}

t_bool		have_spaces(char *str)
{
	while (*str)
	{
		if (ft_isspace(*str))
			return (TRUE);
		str++;
	}
	return (FALSE);
}

void	handle_vars(t_token **tokens, t_command **cmd)
{
	t_command	*last;

	last = get_last_command(*cmd);
	if (!last->name)
	{
		if (have_spaces((*tokens)->str))
			handle_vars_spaces(*tokens, last);
		else
			last->name = ft_strdup((*tokens)->str);
		*tokens = (*tokens)->next;
		return ;
	}
	handle_var_argument(tokens, last);
}

void	handle_vars_spaces(t_token *tokens, t_command *last)
{
	char	**split;

	split = ft_split(tokens->str, ' ');
	last->name = ft_strdup(split[0]);
	last->argv = split;
}

void	handle_var_argument(t_token **tokens, t_command *last)
{
	char	**split;
	char	**argv;
	int		len_args;
	int		new_args_count;

	if (have_spaces((*tokens)->str))
	{
		split = ft_split((*tokens)->str, ' ');
		if (!last->argv)
		{
			last->argv = ft_calloc(array_len(split) + 2, sizeof(char *));
			last->argv[0] = ft_strdup(last->name);
			ft_memmove(last->argv + 1, split, array_len(split) * sizeof(char *));
		}
		else
		{
			len_args = array_len(last->argv);
			new_args_count = array_len(split);
			argv = ft_calloc(len_args + new_args_count + 1, sizeof(char *));
			ft_memmove(argv, last->argv, len_args * sizeof(char *));
			ft_memmove(argv + len_args, split, new_args_count * sizeof (char *));
			free(last->argv);
			last->argv = argv;
		}
		free(split);
	}
	else
	{
		if (!last->argv)
		{
			last->argv = ft_calloc(3, sizeof(char *));
			last->argv[0] = ft_strdup(last->name);
			last->argv[1] = ft_strdup((*tokens)->str);
		}
	}
	*tokens = (*tokens)->next;
}

void	set_commands_with_no_argv(t_command *cmd)
{
	while (cmd)
	{
		if (!cmd->argv)
		{
			cmd->argv = ft_calloc(2, sizeof(char *));
			cmd->argv[0] = ft_strdup(cmd->name);
		}
		cmd = cmd->next;
	}
}

int	get_len_args(t_token *token)
{
	int	i;

	i = 0;
	while (token->type == WORD)
	{
		i++;
		token = token->next;
	}
	return (i);
}

void	get_args(t_token **tokens, t_command *last)
{
	if (!last->argv)
		create_argv(tokens, last);
	else
		add_to_argv(tokens, last);
}

void	create_argv(t_token **tokens, t_command *last)
{
	int		count_args;
	t_token	*tmp;
	int		i;

	tmp = *tokens;
	count_args = get_len_args(*tokens);
	last->argv = ft_calloc(count_args + 2, sizeof(char *));
	last->argv[0] = ft_strdup(last->name);
	i = 1;
	while (tmp->type == WORD)
	{
		last->argv[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	*tokens = tmp;
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	add_to_argv(t_token **tokens, t_command *last)
{
	char	**new_argv;
	int		argv_len;
	int		count_new_args;
	t_token	*tmp;

	argv_len = array_len(last->argv);
	count_new_args = get_len_args(*tokens);
	new_argv = ft_calloc(argv_len + count_new_args + 1, sizeof(char *));
	ft_memmove(new_argv, last->argv, argv_len * sizeof(char *));
	tmp = *tokens;
	while (tmp->type == WORD)
	{
		new_argv[argv_len] = ft_strdup(tmp->str);
		argv_len++;
		tmp = tmp->next;
	}
	free(last->argv);
	last->argv = new_argv;
	*tokens = tmp;
}

void	handle_trunc_append_input(t_token **tokens, t_command *cmd)
{
	t_command	*last;

	last = get_last_command(cmd);
	if (!last->io)
		last->io = ft_calloc(1, sizeof(t_io));
	if ((*tokens)->type == TRUNC || (*tokens)->type == APPEND)
		open_output_file(*tokens, last);
	else
		open_input_file(*tokens, last);
	*tokens = (*tokens)->next->next;
}

void	open_input_file(t_token *tokens, t_command *last)
{
	t_io	*io;

	io = last->io;
	if (io->infile_fd < 0 || io->outfile_fd < 0)
		return ;
	if (io->infile)
	{
		close(io->infile_fd);
		ft_free_ptr((void **)&io->infile);
	}
	if (!io->infile)
		io->infile = ft_strdup(tokens->next->str);
	io->infile_fd = open(io->infile, O_RDONLY, 0);
	if (io->infile_fd < 0)
		ft_printf_fd(2, "%s: %s: %s\n", "Minishell", io->infile,
			strerror(errno));
}

void	open_output_file(t_token *tokens, t_command *last)
{
	t_io	*io;

	io = last->io;
	if (io->outfile_fd < 0 || io->infile_fd < 0)
		return ;
	if (io->outfile)
	{
		close(io->outfile_fd);
		ft_free_ptr((void **)&io->outfile);
	}
	if (!io->outfile)
		io->outfile = ft_strdup(tokens->next->str);
	if (tokens->type == TRUNC)
		io->outfile_fd = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		io->outfile_fd = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (io->outfile_fd < 0)
		ft_printf_fd(2, "%s: %s: %s\n", "Minishell", io->outfile,
			strerror(errno));
}

void	handle_pipe(t_token **token, t_command **cmd)
{
	t_command	*last;

	last = get_last_command(*cmd);
	last->output_to_pipe = TRUE;
	append_command(cmd, new_command(NULL, FALSE));
	*token = (*token)->next;
}

void	handle_words(t_token **token, t_command **cmd)
{
	t_command	*last;
	t_token		*tmp;

	last = get_last_command(*cmd);
	tmp = *token;
	if (!last->name)
	{
		last->name = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	else
		get_args(&tmp, last);
	*token = tmp;
}
