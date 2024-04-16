/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:42:52 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/16 14:42:53 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	has_quotes(char *delimiter)
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

	if (!has_quotes(delimiter))
		return (ft_strdup(delimiter));
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

char	*get_file_name(t_bool is_first)
{
	char				*file_name;
	char				*tmp;
	static int unsigned	number;

	if (is_first)
		number = 0;
	tmp = ft_itoa(number);
	file_name = ft_strjoin(HERE_DOC_FILE, tmp);
	free(tmp);
	number++;
	return (file_name);
}

int unsigned	count_commands(t_token *token)
{
	int unsigned	count;

	count = 0;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count + 1);
}
