/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:30:22 by matesant          #+#    #+#             */
/*   Updated: 2024/04/04 14:34:09 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_spaces(char **str)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	end = ft_strlen(*str) - 1;
	while (ft_isspace((*str)[start]))
		start++;
	while (end >= start && ft_isspace((*str)[end]))
		end--;
	i = start;
	while (i <= end)
	{
		(*str)[i - start] = (*str)[i];
		i++;
	}
	(*str)[i - start] = '\0';
}

char	*ft_forbidden_separators(char *line)
{
	unsigned long	i;
	char			*dot;

	i = 0;
	dot = ".: filename argument required\n.: usage: . filename [arguments]";
	while (line[i])
	{
		ft_skip_quotes(line, &i);
		if ((line[i] == '&' && line[i + 1] == '&'))
			return ("syntax error near unexpected token `&&'");
		else if (line[0] == ';' && !line[1])
			return ("syntax error near unexpected token `;'");
		else if (line[0] == '.' && !line[1])
			return (dot);
		i++;
	}
	return (NULL);
}

t_bool	ft_only_spaces(char *line)
{
	unsigned long	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
