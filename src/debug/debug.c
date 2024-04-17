/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:10:20 by almarcos          #+#    #+#             */
/*   Updated: 2024/03/12 12:15:47 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_argv(t_command *node)
{
	int	i;

	i = 0;
	while (node->argv[i])
	{
		printf("\t\t- argv[%d]: %s\n", i, node->argv[i]);
		i++;
	}
}

static void	print_io(t_command *node)
{
	printf("\t\t- infile: %s\n", node->io->infile);
	printf("\t\t- outfile: %s\n", node->io->outfile);
	printf("\t\t- infile_fd: %d\n", node->io->infile_fd);
	printf("\t\t- outfile_fd: %d\n", node->io->outfile_fd);
}

void	print_cmd_list(t_command *list)
{
	printf("\n\n\n       ------ COMMAND LIST ------\n\n\n");
	while (list)
	{
		printf("\t- Name: %s\n", list->name);
		printf("\t- Path: %s\n", list->path);
		printf("\t- Argv: %p\n", list->argv);
		if (list->argv)
			print_argv(list);
		printf("\t- Output to pipe: %d\n", list->output_to_pipe);
		printf("\t- Io: %p\n", list->io);
		if (list->io)
			print_io(list);
		printf("\t- Prev: %p\n", list->prev);
		if (list->prev)
			printf("\t\t- Name: %s\n", list->prev->name);
		printf("\t- Next: %p\n", list->next);
		if (list->next)
			printf("\t\t- Name: %s\n", list->next->name);
		list = list->next;
		printf("\n   ===================================\n\n");
	}
}
