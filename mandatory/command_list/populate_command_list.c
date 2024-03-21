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

void	get_args(t_token **tokens, t_command *last)
{
	if (!last->argv)
		create_argv(tokens, last);
	else
		add_to_argv(tokens, last);
}

void	create_argv(t_token **tokens, t_command *last)
{
	int			count_args;
	t_token		*tmp;
	int			i;

	tmp = *tokens;
	count_args = get_len_args(*tokens);
	last->argv = ft_calloc(count_args + 2, sizeof (char *));
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

int		array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	add_to_argv(t_token **tokens, t_command *last)
{
	char		**new_argv;
	int			argv_len;
	int			count_new_args;
	t_token		*tmp;

	argv_len = array_len(last->argv);
	count_new_args = get_len_args(*tokens);
	new_argv = ft_calloc(argv_len + count_new_args + 1, sizeof (char *));
	ft_memmove(new_argv, last->argv, argv_len * sizeof (char *));
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
