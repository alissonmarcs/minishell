/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:24:54 by matesant          #+#    #+#             */
/*   Updated: 2024/04/12 12:12:04 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_minishell *shell)
{
	t_command	*cmds;

	cmds = shell->commands;
	if (is_builtin(cmds, TRUE))
	{
		execute_builtin(cmds, FALSE);
		return ;
	}
	create_pipes(cmds);
	while (cmds)
	{
		cmd_signal();
		cmds->pid = fork();
		if (cmds->pid == 0)
			run_commands(shell, cmds);
		cmds = cmds->next;
	}
	close_pipes(shell->commands, NULL);
	wait_childs(shell);
}

void	run_commands(t_minishell *shell, t_command *cmd)
{
	if (!check_redirect_files(cmd))
	{
		shell->exit_status = 1;
		clear_exit(shell, TRUE);
	}
	if (!cmd->name || !cmd->name[0])
	{
		shell->exit_status = 0;
		clear_exit(shell, TRUE);
	}
	set_pipes(cmd);
	set_redirects(cmd);
	close_redirect_files(cmd);
	close_pipes(shell->commands, cmd);
	execute_piped_builtins(cmd);
	cmd->path = find_executable(cmd);
	if (cmd->path)
		execve(cmd->path, cmd->argv, shell->env);
	execve(cmd->name, cmd->argv, shell->env);
	handle_execve_error(shell, cmd);
}

void	get_captalized_errors(t_command *cmd)
{
	int		exit_status;
	char	*error_msg;

	if (access(cmd->name, F_OK) < 0)
	{
		error_msg = "No such file or directory";
		exit_status = 127;
	}
	else if (access(cmd->name, X_OK) == 0)
	{
		error_msg = "Is a directory";
		exit_status = 126;
	}
	else
	{
		error_msg = "Permission denied";
		exit_status = 126;
	}
	ft_printf_fd(2, "%s: %s: %s\n", "Minishell", cmd->name, error_msg);
	ft_get_shell()->exit_status = exit_status;
	clear_exit(ft_get_shell(), TRUE);
}

void	handle_execve_error(t_minishell *shell, t_command *cmd)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strchr(cmd->name, '/') || cmd->name[0] == '.')
		get_captalized_errors(cmd);
	else
	{
		ft_printf_fd(2, "%s: %s: %s\n", "Minishell", cmd->name,
			"command not found");
		exit_status = 127;
	}
	shell->exit_status = exit_status;
	clear_exit(shell, TRUE);
}

void	wait_childs(t_minishell *shell)
{
	int			status;
	t_command	*cmd;

	cmd = shell->commands;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
	shell->exit_status = WEXITSTATUS(status);
}	
