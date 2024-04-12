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

char	*get_var(char *line)
{
	int		i;
	char	*ptr;

	i = 1;
	ptr = ft_strchr(line, '$');
	if (!ptr)
		return (NULL);
	
	while (ptr[i] && ft_isalnum(ptr[i]))
		i++;
	
	if (ptr[i] == '?')
		i++;

	return (ft_substr(ptr, 0, i));
}

t_bool ft_has_dolar(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (line[i + 1] == '?')
				return (1);
			if (ft_isalnum(line[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

char	*expand_vars(char *line)
{
	char	*var;

	while (ft_has_dolar(line))
	{
		var = get_var(line);
		line = ft_replace_noi(var, ft_getenv(var + 1), line);
		continue ;
	}
	return (line);
}
