/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:56:53 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/16 18:56:55 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
