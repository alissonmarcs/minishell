/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:33:55 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/16 14:33:56 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_input_file(t_token *tokens, t_command *last);
static void	open_output_file(t_token *tokens, t_command *last);

void	handle_trunc_append_input(t_token **tokens, t_command *last)
{
	if (!last->io)
		last->io = ft_calloc(1, sizeof(t_io));
	if ((*tokens)->type == TRUNC || (*tokens)->type == APPEND)
		open_output_file(*tokens, last);
	else
		open_input_file(*tokens, last);
	*tokens = (*tokens)->next->next;
}

static void	open_input_file(t_token *tokens, t_command *last)
{
	t_io	*io;

	io = last->io;
	if (io->infile_fd < 0 || io->outfile_fd < 0)
		return ;
	if (io->infile)
	{
		close(io->infile_fd);
		ft_free_ptr((void **)&io->infile);
	}
	if (!io->infile)
		io->infile = ft_strdup(tokens->next->str);
	io->infile_fd = open(io->infile, O_RDONLY | O_CLOEXEC, 0);
	if (io->infile_fd < 0)
		ft_printf_fd(2, "%s: %s: %s\n", "Minishell", io->infile,
			strerror(errno));
}

static void	open_output_file(t_token *tokens, t_command *last)
{
	t_io	*io;

	io = last->io;
	if (io->outfile_fd < 0 || io->infile_fd < 0)
		return ;
	if (io->outfile)
	{
		close(io->outfile_fd);
		ft_free_ptr((void **)&io->outfile);
	}
	if (!io->outfile)
		io->outfile = ft_strdup(tokens->next->str);
	if (tokens->type == TRUNC)
		io->outfile_fd = open(io->outfile, O_WRONLY | O_CREAT
				| O_TRUNC | O_CLOEXEC, 420);
	else
		io->outfile_fd = open(io->outfile, O_WRONLY | O_CREAT
				| O_APPEND | O_CLOEXEC, 420);
	if (io->outfile_fd < 0)
		ft_printf_fd(2, "%s: %s: %s\n", "Minishell", io->outfile,
			strerror(errno));
}
