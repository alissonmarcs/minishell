/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:42:56 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/16 14:42:57 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init_heredocs(t_token *tokens);
static void		populate_file(char *file, t_bool quotes, char *delimiter);
static void		here_doc_loop(int fd, t_bool quotes, char *delimiter);
static t_bool	execute_here_doc(char *delimiter, int unsigned index,
					t_heredoc *hd, t_bool is_first);

t_bool	check_here_docs(t_minishell *shell)
{
	unsigned int	command_index;
	t_token			*tokens;

	command_index = 0;
	tokens = shell->tokens;
	init_heredocs(tokens);
	while (tokens)
	{
		if (tokens->type == PIPE)
			command_index++;
		else if (tokens->type == HERE_DOC)
		{
			if (!execute_here_doc(tokens->next->str, command_index,
					shell->heredocs, tokens->prev == NULL))
				return (FALSE);
		}
		tokens = tokens->next;
	}
	return (TRUE);
}

static void	init_heredocs(t_token *tokens)
{
	t_heredoc	*hd;

	hd = ft_calloc(1, sizeof(t_heredoc));
	hd->size = count_commands(tokens);
	hd->array = ft_calloc(hd->size, sizeof(t_herdoc_file *));
	ft_get_shell()->heredocs = hd;
}

static t_bool	execute_here_doc(char *delimiter, int unsigned index,
		t_heredoc *hd, t_bool is_first)
{
	char	*file;
	pid_t	pid;
	int		exit_status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	file = get_file_name(is_first);
	append_file(&hd->array[index], new_file(file));
	pid = fork();
	if (pid == 0)
		populate_file(file, has_quotes(delimiter), remove_quotes(delimiter));
	waitpid(pid, &exit_status, 0);
	exit_status = WEXITSTATUS(exit_status);
	ft_get_shell()->exit_status = exit_status;
	if (exit_status == 130)
		return (FALSE);
	return (TRUE);
}

static void	populate_file(char *file, t_bool quotes, char *delimiter)
{
	int		fd;

	signal(SIGINT, ctrl_c_heredoc);
	ft_rlstnew(delimiter);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	here_doc_loop(fd, quotes, delimiter);
	close(fd);
	ft_get_shell()->exit_status = 0;
	clear_exit(ft_get_shell(), TRUE);
}

static void	here_doc_loop(int fd, t_bool quotes, char *delimiter)
{
	char	*line;

	while (TRUE)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf_fd(2, "%s %s %s (wanted `%s')\n", "Minishell:",
				"warning:", "here-document delimited by end-of-file",
				delimiter);
			break ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (!quotes)
			line = expand_vars(line);
		ft_putendl_fd(line, fd);
		free(line);
	}
}
