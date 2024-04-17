/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:08:24 by matesant          #+#    #+#             */
/*   Updated: 2024/04/12 17:27:44 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*get_var(char *line);
static	char	*has_var(char *line);
static	char	*replace(char *old, char *new, char *str);

char	*expand_vars(char *line)
{
	char	*var;

	while (has_var(line))
	{
		var = get_var(line);
		line = replace(var, ft_getenv(var + 1), line);
	}
	return (line);
}

static char	*get_var(char *line)
{
	int		i;
	char	*ptr;

	i = 1;
	ptr = has_var(line);
	while (ptr[i] && ft_isalnum(ptr[i]))
		i++;
	if (ptr[i] == '?')
		i++;
	return (ft_substr(ptr, 0, i));
}

static char	*has_var(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			if (line[i + 1] == '?' || ft_isalnum(line[i + 1]))
				return (line + i);
		}
		i++;
	}
	return (NULL);
}

static	char	*replace(char *old, char *new, char *str)
{
	char	*result;
	char	*ptr;
	char	*before;
	char	*with_var;

	ptr = ft_strnstr(str, old, ft_strlen(str));
	before = ft_substr(str, 0, ptr - str);
	with_var = ft_strjoin(before, new);
	free(new);
	free(before);
	before = ft_substr(str, ptr - str + ft_strlen(old), ft_strlen(str));
	free(old);
	free(str);
	old = NULL;
	result = ft_strjoin(with_var, before);
	free(before);
	free(with_var);
	return (result);
}
