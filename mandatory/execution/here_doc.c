#include "minishell.h"

t_bool	check_here_docs(t_minishell *shell)
{
	unsigned	command_index;
	t_token		*tokens;

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

void	init_heredocs(t_token *tokens)
{
	t_heredoc	*hd;

	hd = ft_calloc(1, sizeof(t_heredoc));
	hd->size = count_commands(tokens);
	hd->array = ft_calloc(hd->size, sizeof(t_herdoc_file *));
	ft_get_shell()->heredocs = hd;
}

t_bool	execute_here_doc(char *delimiter, unsigned index, t_heredoc *hd,
		t_bool is_first)
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
		populate_file(file, delimiter);
	waitpid(pid, &exit_status, 0);
	exit_status = WEXITSTATUS(exit_status);
	ft_get_shell()->exit_status = exit_status;
	if (exit_status == 130)
		return (FALSE);
	return (TRUE);
}

void	populate_file(char *file, char *delimiter)
{
	char	*line;
	int		fd;

	signal(SIGINT, ctrl_c_heredoc);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
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
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	clear_exit(ft_get_shell(), 0);
}

char	*get_file_name(t_bool is_first)
{
	char			*file_name;
	char			*tmp;
	static unsigned	number;

	if (is_first)
		number = 0;
	tmp = ft_itoa(number);
	file_name = ft_strjoin(HERE_DOC_FILE, tmp);
	free(tmp);
	number++;
	return (file_name);
}

unsigned	count_commands(t_token *token)
{
	unsigned	count;

	count = 0;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count + 1);
}

t_herdoc_file	*new_file(char *file_name)
{
	t_herdoc_file	*node;

	node = ft_calloc(1, sizeof(t_herdoc_file));
	node->file = file_name;
	return (node);
}

t_herdoc_file	*get_last_file(t_herdoc_file *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	append_file(t_herdoc_file **head, t_herdoc_file *new)
{
	if (!*head)
		*head = new;
	else
		get_last_file(*head)->next = new;
}

void	free_here_docs(t_heredoc *hd)
{
	unsigned		i;
	t_herdoc_file	*next;
	t_herdoc_file	*current;

	if (!hd)
		return ;
	i = 0;
	while (i < hd->size)
	{
		current = hd->array[i];
		while (current)
		{
			next = current->next;
			free(current->file);
			free(current);
			current = next;
		}
		i++;
	}
	free(hd->array);
	free(hd);
}
