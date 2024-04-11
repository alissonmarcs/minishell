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
		populate_file(file, have_quotes(delimiter), remove_quotes(delimiter));
	waitpid(pid, &exit_status, 0);
	exit_status = WEXITSTATUS(exit_status);
	ft_get_shell()->exit_status = exit_status;
	if (exit_status == 130)
		return (FALSE);
	return (TRUE);
}

t_bool	have_quotes(char *delimiter)
{
	while (*delimiter)
	{
		if (*delimiter == '\'' || *delimiter == '\"')
			return (TRUE);
		delimiter++;
	}
	return (FALSE);
}

char	*remove_quotes(char *delimiter)
{
	int		len;
	char	*new;
	char	*tmp;

	len = ft_strlen(delimiter);
	new = ft_calloc(len + 1, sizeof(char));
	tmp = new;
	while (*delimiter)
	{
		if (*delimiter != '\'' && *delimiter != '\"')
		{
			*tmp = *delimiter;
			tmp++;
		}
		delimiter++;
	}
	return (new);
}

void	populate_file(char *file, t_bool have_quotes, char *delimiter)
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
		if (!have_quotes)
			line = expand_vars(line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	free(delimiter);
	clear_exit(ft_get_shell(), 0);
}

int	len_next_non_alphanum(char *str)
{
	int	len;

	len = 1;
	if (str[len] == '?')
		return (len + 1);
	while (str[len] && ft_isalnum(str[len]))
		len++;
	return (len);
}

char	*get_var(char *line)
{
	int		i;
	char	*ptr;
	int		num_dolars;

	i = -1;
	num_dolars = 0;
	while (line[++i])
	{
		if (line[i] == '$')
			num_dolars++;
	}
	ptr = line;
	while (num_dolars)
	{
		ptr = ft_strchr(ptr, '$');
		if (ft_isalnum(ptr[1]) || ptr[1] == '?')
			return (ptr);
		num_dolars--;
		ptr++;
	}
	return (NULL);
}

char	*expand_vars(char *line)
{
	char	*before;
	char	*var_name;
	char	*var_value;
	char	*after;
	char	*tmp;
	int		len;

	while (get_var(line))
	{
		tmp = get_var(line);
		before = ft_substr(line, 0, tmp - line);
		len = len_next_non_alphanum(tmp);
		var_name = ft_substr(tmp, 0, len);
		var_value = ft_getenv(var_name + 1);
		after = ft_strdup(tmp + len);
		if (var_value[0] == '\0')
		{
			free(line);
			line = ft_strjoin_tree(before, after, NULL);
			free(var_name);
			free(var_value);
			continue ;
		}
		free(var_name);
		free(line);
		line = ft_strjoin_tree(before, var_value, after);
	}
	return (line);
}

char *ft_strjoin_tree(char *one, char *two, char *three)
{
	char *tmp;
	char *joined;

	tmp = ft_strjoin(one, two);
	free(one);
	free(two);
	if (three)
	{
		joined = ft_strjoin(tmp, three);
		free(three);
		free(tmp);
		return (joined);
	}
	return (tmp);
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

void free_here_docs(t_heredoc **hd)
{
	unsigned		i;
	t_herdoc_file	*next;
	t_herdoc_file	*current;

	if (!*hd)
		return ;
	i = 0;
	while (i < (*hd)->size)
	{
		current = (*hd)->array[i];
		while (current)
		{
			next = current->next;
			free(current->file);
			free(current);
			current = next;
		}
		i++;
	}
	free((*hd)->array);
	free(*hd);
	*hd = NULL;
}
