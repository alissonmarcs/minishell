/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:31:27 by matesant          #+#    #+#             */
/*   Updated: 2024/04/05 14:30:02 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_separator(char *str)
{
	if (!ft_strncmp(str, " ", 1) || !ft_strncmp(str, "\t", 1)
		|| !ft_strncmp(str, "\n", 1) || !ft_strncmp(str, "\v", 1)
		|| !ft_strncmp(str, "\f", 1) || !ft_strncmp(str, "\r", 1))
		return (SPACES);
	else if (!ft_strncmp(str, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(str, "<<", 2))
		return (HERE_DOC);
	else if (!ft_strncmp(str, ">", 1))
		return (TRUNC);
	else if (!ft_strncmp(str, "<", 1))
		return (INPUT);
	else if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	else if (*str == '\0')
		return (END);
	else
		return (0);
}

void	ft_word(char *word, int start, int end, t_minishell *shell)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		ft_error("malloc error", 900);
	while (start < end)
	{
		str[i++] = word[start++];
	}
	str[i] = '\0';
	ft_lstend(&shell->tokens, str, WORD);
}

void	ft_separator(char *separator, t_minishell *shell, int start, int type)
{
	char	*str;
	int		i;

	i = 0;
	if (type == APPEND || type == HERE_DOC)
	{
		str = malloc(sizeof(char) * 3);
		while (i < 2)
			str[i++] = separator[start++];
		str[i] = '\0';
		ft_lstend(&shell->tokens, str, type);
	}
	else
	{
		str = malloc(sizeof(char) * 2);
		while (i < 1)
			str[i++] = separator[start++];
		str[i] = '\0';
		ft_lstend(&shell->tokens, str, type);
	}
}

void	ft_words_separators(char *input, t_minishell *shell)
{
	int				type;
	unsigned long	i;
	int				start;

	start = 0;
	i = -1;
	while (input && ++i < ft_strlen(input) + 1)
	{
		ft_skip_quotes(input, &i);
		type = ft_is_separator(&input[i]);
		if (type)
		{
			if (i != 0 && !ft_is_separator(&input[i - 1]))
				ft_word(input, start, i, shell);
			if (type != SPACES && type != VAR && type != WORD)
			{
				ft_separator(input, shell, i, type);
				if (type == APPEND || type == HERE_DOC)
					i++;
			}
			start = i + 1;
		}
	}
}

t_bool	ft_tokenize(t_minishell *shell)
{
	char	*line;

	line = shell->user_input;
	if (ft_pre_token_err(line))
		return (TRUE);
	ft_words_separators(shell->user_input, shell);
	if (ft_error(ft_check_syntax(shell->tokens), 2))
		return (TRUE);
	if (ft_var_expansion())
		ft_error("error", 2);
	ft_remove_quotes();
	return (FALSE);
}
