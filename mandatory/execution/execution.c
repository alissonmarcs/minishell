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
		if (cmd->output_to_pipe)
			pipe(cmds->pipe);
		cmds = cmds->next;
	}
}

void	close_needless_pipes(t_command *cmds, t_command *to_keep)
{
	while (cmds)
	{
		if (cmds != to_keep)
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
		dup2(cmd->pipe[1], STDOUT_FILENO);
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
	if ((io->infile && io->infile_fd < 0) ||
		(io->outfile && io->outfile_fd) < 0)
		return (FALSE);
	return (TRUE);
}

void	set_redirects(t_command *cmd)
{
	t_io	*io;

	io = cmd;
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
	if (io->infile_fd > 0)
		close(io->infile_fd);
	if (io->outfile_fd > 0)
		close(io->outfile_fd);
}

char	*find_executable(t_minishell *shell, t_command *cmd)
{
	
}