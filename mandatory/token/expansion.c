/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:35:49 by matesant          #+#    #+#             */
/*   Updated: 2024/04/12 10:31:12 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_var(char *str, int *i)
{
	int		j;
	char	*line;

	j = 1;
	line = str;
	line += (*i);
	if (!line)
		return (NULL);
	while (line[j] && ft_isalnum(line[j]))
		j++;
	if (line[j] == '?')
		j++;
	return (ft_substr(line, 0, j));
}

t_bool	ft_inflation(char *input, char **var)
{
	int		i;
	char	*line;

	i = 0;
	line = input;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '$')
		{
			line = ft_strchr(line, '$');
			*var = (ft_substr(line, 0, 2));
			return (FALSE);
		}
		line += 1;
		i++;
	}
	return (TRUE);
}

t_bool	ft_dollars_in_my_pocket(char *input, int *i, int *status)
{
	while (input[(*i)])
	{
		(*status) = ft_quotes_status(input[(*i)], (*status));
		if (input[(*i)] == '$' && input[(*i) + 1] == '$' && ((*status) == 0
				|| (*status) == 1))
			return (TRUE);
		if (input[(*i)] == '$' && ((*status) == 0 || (*status) == 1)
			&& ft_isalpha(input[(*i) + 1]) == 1)
			return (TRUE);
		if (input[(*i)] == '$' && input[(*i) + 1] == '?' && ((*status) == 0
				|| (*status) == 1))
			return (TRUE);
		(*i)++;
	}
	return (FALSE);
}

t_bool	ft_var_expansion(void)
{
	static int	i;
	static int	status;
	char		*var;
	t_token		*curr;

	curr = ft_get_shell()->tokens;
	while (curr && curr->type != END)
	{
		if (curr->prev && curr->prev->type == HERE_DOC)
		{
			curr = curr->next;
			continue ;
		}
		if (ft_dollars_in_my_pocket(curr->str, &i, &status))
		{
			if (ft_inflation(curr->str, &var))
				var = ft_find_var(curr->str, &i);
			curr->str = ft_replace(var, ft_getenv(var + 1), curr->str, &i);
			curr->type = VAR;
			continue ;
		}
		ft_replace_teemo(curr, ft_get_shell()->teemo, &i, &status);
		curr = curr->next;
	}
	return (FALSE);
}
