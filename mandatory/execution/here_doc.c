#include "minishell.h"

t_bool	populate_heredocs(t_minishell *shell)
{
	unsigned	index;
	t_token		*tokens;

	index = 0;
	tokens = shell->tokens;
	init_heredocs(tokens);
	while (tokens)
	{
		if (tokens->type == PIPE)
			index++;
		else if (tokens->type == HERE_DOC)
		{
			if (!here_doc_loop(tokens->next->str, index, shell->heredocs, tokens->prev == NULL))
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
	hd->array = ft_calloc(hd->size, sizeof(t_hd_node *));
	ft_get_shell()->heredocs = hd;
}

t_bool	here_doc_loop(char *delimiter, unsigned index, t_heredoc *hd, t_bool is_first)
{
	char	*line;
	int		fd;
	char	*file_name;
	int		exit_status;
	pid_t	pid;

	file_name = get_file_name(is_first);
	append_hd(&hd->array[index], new_hd(file_name));
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, ctrl_c_heredoc);
		signal(SIGQUIT, SIG_IGN);
		fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		while (TRUE)
		{
			line = readline("> ");
			if (!line)
			{
				ft_printf_fd(2, "terminated by EOF\n");
				break ;
			}
			if (ft_strcmp(line, delimiter) == 0)
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
	waitpid(pid, &exit_status, 0);
	exit_status = WEXITSTATUS(exit_status);
	ft_get_shell()->exit_status = exit_status;
	if (exit_status == 130)
		return (FALSE);
	return (TRUE);
}

char *get_file_name(t_bool is_first)
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

unsigned count_commands(t_token *token)
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

t_hd_node *new_hd(char *file_name)
{
	t_hd_node	*node;

	node = ft_calloc(1, sizeof(t_hd_node));
	node->file = file_name;
	return (node);
}

t_hd_node *get_last_hd(t_hd_node *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void append_hd(t_hd_node **head, t_hd_node *new)
{
	if (!*head)
		*head = new;
	else
		get_last_hd(*head)->next = new;
}

void free_hd(t_heredoc *hd)
{
	unsigned 	i;
	t_hd_node	*next;
	t_hd_node	*current;

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
