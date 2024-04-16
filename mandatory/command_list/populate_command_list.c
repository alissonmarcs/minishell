/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_command_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:03:30 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/03 06:19:02 by matesant         ###   ########.fr       */
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
	t_token			*token;
	t_command		*command;
	unsigned int	command_index;

	command_index = 0;
	token = shell->tokens;
	command = shell->commands;
	add_dummy_node(&command);
	while (token)
	{
		if (token->type == WORD)
			handle_words(&token, get_last_command(command));
		else if (token->type == PIPE)
			handle_pipe(&token, &command, &command_index);
		else if (token->type == TRUNC || token->type == APPEND
			|| token->type == INPUT)
			handle_trunc_append_input(&token, get_last_command(command));
		else if (token->type == VAR)
			handle_vars(&token, get_last_command(command));
		else if (token->type == HERE_DOC)
			handle_heredoc(&token, get_last_command(command), command_index);
		else if (token->type == END)
			break ;
	}
	shell->commands = command;
}

void	handle_heredoc(t_token **tokens, t_command *last,
	unsigned int command_index)
{
	t_io			*io;
	t_herdoc_file	**array;
	t_herdoc_file	*current;

	if (!last->io)
		last->io = ft_calloc(1, sizeof(t_io));
	io = last->io;
	array = ft_get_shell()->heredocs->array;
	if (check_redirect_files(last))
	{
		if (io->infile)
		{
			free(io->infile);
			close(io->infile_fd);
		}
		io->infile = ft_strdup(array[command_index]->file);
		io->infile_fd = open(io->infile, O_RDONLY | O_CLOEXEC, 0);
		current = array[command_index];
		array[command_index] = array[command_index]->next;
		free(current->file);
		free(current);
	}
	*tokens = (*tokens)->next->next;
}

void	handle_pipe(t_token **token, t_command **cmd,
				unsigned int *command_index)
{
	t_command	*last;

	last = get_last_command(*cmd);
	last->output_to_pipe = TRUE;
	append_command(cmd, new_command(NULL, FALSE));
	*token = (*token)->next;
	(*command_index)++;
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
