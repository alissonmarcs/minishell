/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:56:37 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/16 18:58:10 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_command *cmd, t_bool is_piped)
{
	if (!check_redirect_files(cmd))
	{
		ft_get_shell()->exit_status = 1;
		return ;
	}
	set_redirects(cmd);
	close_redirect_files(cmd);
	if (ft_strcmp(cmd->name, "cd") == 0)
		ft_cd_builtin(cmd->argv);
	else if (ft_strcmp(cmd->name, "env") == 0)
		ft_env_builtin(cmd->argv);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		ft_exit(cmd->argv);
	else if (ft_strcmp(cmd->name, "export") == 0)
		ft_export(cmd->argv);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		ft_unset(cmd->argv);
	else if (ft_strcmp(cmd->name, "echo") == 0)
		ft_echo_builtin(cmd->argv);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		ft_pwd_builtin(cmd->argv);
	if (!is_piped)
		restore_standard_fds(ft_get_shell());
}

t_bool	is_builtin(t_command *cmds, t_bool check_if_alone)
{
	t_bool	is_builtin;

	is_builtin = FALSE;
	if (ft_strcmp(cmds->name, "cd") == 0
		|| ft_strcmp(cmds->name, "env") == 0
		|| ft_strcmp(cmds->name, "exit") == 0
		|| ft_strcmp(cmds->name, "export") == 0
		|| ft_strcmp(cmds->name, "unset") == 0
		|| ft_strcmp(cmds->name, "echo") == 0
		|| ft_strcmp(cmds->name, "pwd") == 0)
		is_builtin = TRUE;
	if (check_if_alone)
	{
		if (!cmds->next && is_builtin)
			return (TRUE);
		return (FALSE);
	}
	return (is_builtin);
}

void	execute_piped_builtins(t_command *cmd)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	if (is_builtin(cmd, FALSE))
	{
		execute_builtin(cmd, TRUE);
		clear_exit(shell, TRUE);
	}
}

void	copy_standard_fds(t_minishell *shell)
{
	shell->standard_fds[0] = dup(STDIN_FILENO);
	shell->standard_fds[1] = dup(STDOUT_FILENO);
}

void	restore_standard_fds(t_minishell *shell)
{
	dup2(shell->standard_fds[0], STDIN_FILENO);
	dup2(shell->standard_fds[1], STDOUT_FILENO);
}
