/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_command_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:03:30 by almarcos          #+#    #+#             */
/*   Updated: 2024/03/12 12:16:09 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_dummy_node(t_command **cmd)
{
	t_command	*dummy;

	dummy = new_command(NULL, false);
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
		else if (token->type == TRUNC || token->type == INPUT)
			handle_truc_input(&token, command);
		else if (token->type == END)
			break ;
	}
	set_commands_with_no_argv(command);
	shell->commands = command;
}

void	set_commands_with_no_argv(t_command *cmd)
{
	while (cmd)
	{
		if (!cmd->argv)
		{
			cmd->argv = ft_calloc(2, sizeof (char *));
			cmd->argv[0] = ft_strdup(cmd->name);
		}
		cmd = cmd->next;
	}
}

void	handle_truc_input(t_token **token, t_command *cmd)
{
	t_command	*last;

	last = get_last_command(cmd);
	if (!last->io)
		last->io = ft_calloc(1, sizeof (t_io));
	if ((*token)->type == TRUNC)
		last->io->outfile = ft_strdup((*token)->next->str);
	else
		last->io->infile = ft_strdup((*token)->next->str);
	*token = (*token)->next->next;
}

void	handle_pipe(t_token **token, t_command **cmd)
{
	t_command	*last;

	last = get_last_command(*cmd);
	last->output_to_pipe = true;
	append_command(cmd, new_command(NULL, false));
	*token = (*token)->next;
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

void	get_args(t_token **token, t_command *last)
{
	t_token	*current;
	int		i;

	current = *token;
	i = 1;
	last->argv[0] = ft_strdup(last->name);
	while (current->type == WORD)
	{
		last->argv[i] = ft_strdup(current->str);
		i++;
		current = current->next;
	}
	*token = current;
}

void	handle_words(t_token **token, t_command **cmd)
{
	t_command	*last;
	int			len_args;

	last = get_last_command(*cmd);
	if (!last->name)
	{
		last->name = ft_strdup((*token)->str);
		*token = (*token)->next;
	}
	else
	{
		len_args = get_len_args(*token) + 2;
		last->argv = ft_calloc(len_args, sizeof(char *));
		if (!last->argv)
			return ;
		get_args(token, last);
	}
}
