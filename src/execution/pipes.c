/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:57:00 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/16 18:57:01 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_command *cmds)
{
	while (cmds)
	{
		if (cmds->output_to_pipe)
			pipe(cmds->pipe);
		cmds = cmds->next;
	}
}

void	close_pipes(t_command *cmds, t_command *to_keep)
{
	while (cmds)
	{
		if (cmds != to_keep && cmds->output_to_pipe)
		{
			close(cmds->pipe[0]);
			close(cmds->pipe[1]);
		}
		cmds = cmds->next;
	}
}

void	set_pipes(t_command *cmd)
{
	if (cmd->output_to_pipe)
	{
		dup2(cmd->pipe[1], STDOUT_FILENO);
		close(cmd->pipe[0]);
		close(cmd->pipe[1]);
	}
	if (cmd->prev && cmd->prev->output_to_pipe)
		dup2(cmd->prev->pipe[0], STDIN_FILENO);
}

static void	close_all_fds(void)
{
	int	i;

	i = 0;
	while (i <= 1024)
		close(i++);
}

void	clear_exit(t_minishell *shell, t_bool to_exit)
{
	ft_free_ptr((void **) &shell->user_input);
	ft_free_tokens(shell);
	free_cmd_list(&shell->commands);
	free_here_docs(&shell->heredocs);
	ft_garbage_clear(&shell->gc);
	ft_delete_matrice(shell->env);
	shell->env = NULL;
	if (to_exit)
	{
		ft_free_env(shell);
		close_all_fds();
		exit(shell->exit_status);
	}
}
