/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:22:14 by almarcos          #+#    #+#             */
/*   Updated: 2024/03/11 10:22:16 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_command(char *name, bool pipe)
{
	t_command *command;

	command = ft_calloc(1, sizeof (t_command));
	if (!command)
		return (NULL);
	command->name = name;
	command->output_to_pipe = pipe;
	return (command);
}

void	append_command(t_command **cmd_list, t_command *new)
{
	t_command *tail;

	if (!*cmd_list)
		*cmd_list = new;
	else
	{
		tail = get_last_command(*cmd_list);
		tail->next = new;
		new->prev = tail;
	}
}



void	free_cmd_list(t_command **cmd_list)
{
	t_command *tmp;
	t_command *next;

	tmp = *cmd_list;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->argv)
			ft_delete_matrice(tmp->argv);
		free(tmp->name);
		free(tmp);
		tmp = next;
	}
	*cmd_list = NULL;
}

t_command		*get_last_command(t_command *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}
