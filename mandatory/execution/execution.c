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

void	restore_standard_fds(t_minishell *shell)
{
	dup2(shell->standard_fds[0], STDIN_FILENO);
	dup2(shell->standard_fds[1], STDOUT_FILENO);
}

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

t_bool	check_redirect_files(t_command *cmd)
{
	t_io	*io;

	io = cmd->io;
	if (!io)
		return (TRUE);
	if (!io->infile && !io->outfile)
		return (TRUE);
	if ((io->infile && (io->infile_fd < 0)) || (io->outfile
			&& (io->outfile_fd < 0)))
		return (FALSE);
	return (TRUE);
}

void	set_redirects(t_command *cmd)
{
	t_io	*io;

	io = cmd->io;
	if (!io)
		return ;
	if (io->infile_fd > 0)
		dup2(io->infile_fd, STDIN_FILENO);
	if (io->outfile_fd > 0)
		dup2(io->outfile_fd, STDOUT_FILENO);
}

void	close_redirect_files(t_command *cmd)
{
	t_io	*io;

	io = cmd->io;
	if (!io)
		return ;
	if (io->infile_fd > 2)
		close(io->infile_fd);
	if (io->outfile_fd > 2)
		close(io->outfile_fd);
}

char	**get_paths(void)
{
	char	**paths;
	char	*path;

	path = ft_getenv("PATH");
	if (path[0] == '\0')
	{
		free(path);
		return (NULL);
	}
	paths = ft_split(path, ':');
	free(path);
	return (paths);
}

char	*find_executable(t_command *cmd)
{
	char	*executable;
	char	**paths;
	char	*tmp;
	int		i;

	if (!cmd->name)
		return (NULL);
	if (access(cmd->name, X_OK) == 0)
		return (ft_strdup(cmd->name));
	paths = get_paths();
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		executable = ft_strjoin(tmp, cmd->name);
		free(tmp);
		if (access(executable, X_OK) == 0)
		{
			ft_delete_matrice(paths);
			return (executable);
		}
		free(executable);
	}
	ft_delete_matrice(paths);
	return (NULL);
}

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

void	clear_exit(t_minishell *shell, int exit_status)
{
	free(shell->user_input);
	ft_delete_matrice(shell->env);
	ft_free_tokens(shell);
	ft_free_env(shell);
	close_pipes(shell->commands, NULL);
	free_cmd_list(&shell->commands);
	free_here_docs(&shell->heredocs);
	shell->exit_status = exit_status;
	close(shell->standard_fds[0]);
	close(shell->standard_fds[1]);
	exit(exit_status);
}

void execute_piped_builtins(t_command *cmd)
{
	t_minishell *shell;

	if (is_builtin(cmd, FALSE))
	{
		execute_builtin(cmd, TRUE);
		shell = ft_get_shell();
		clear_exit(shell, shell->exit_status);
	}
}

void	run_commands(t_minishell *shell, t_command *cmd)
{
    if (!check_redirect_files(cmd))
		clear_exit(shell, 1);
	if (!cmd->name || !cmd->name[0])
		clear_exit(shell, 0);
	set_pipes(cmd);
	set_redirects(cmd);
	close_redirect_files(cmd);
	close_pipes(shell->commands, cmd);
	execute_piped_builtins(cmd);
	cmd->path = find_executable(cmd);
	if (!cmd->path)
	{
		ft_printf_fd(2, "%s: %s\n", cmd->name, "command not found");
		clear_exit(shell, 127);
	}
	execve(cmd->path, cmd->argv, shell->env);
	ft_printf_fd(2, "%s: %s: %s\n", "Minishell", cmd->name, strerror(errno));
	clear_exit(shell, 5);
}

char	**list_to_array(t_env *vars)
{
	char			**array;
	t_env			*tmp;
	unsigned	int	len;
	unsigned	int	i;

	len = 0;
	tmp = vars;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	array = ft_calloc(len + 1, sizeof(char *));
	tmp = vars;
	i = 0;
	while (tmp)
	{
		array[i] = ft_strjoin_three(tmp->key, "=", tmp->value, FALSE);
		i++;
		tmp = tmp->next;
	}
	return (array);
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
