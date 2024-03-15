/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:35:49 by matesant          #+#    #+#             */
/*   Updated: 2024/03/15 19:13:18 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_and_extract(char **line, char **init, char **var, char **end)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*line)[i] && (*line)[i] != '$')
		i++;
	*init = ft_substr(*line, 0, i);
	if (*line[i] == '$')
		i++;
	printf("init: %s\n", *init);
	while ((*line)[i + j] && ft_isalnum((*line)[i + j]) == 1)
		j++;
	*end = ft_substr(*line, i + j, ft_strlen(*line) - (i + j));
	printf("end: %s\n", *end);
	*var = ft_substr(*line, i, j);
	printf("var: %s\n", *var);
}

void	ft_expand_and_manage(char **line, char *init, char *var, char *end)
{
	char	*final;
	char	*linha;

	final = getenv(var);
	if (final)
	{
		linha = ft_strjoin(init, final);
		*line = ft_strjoin(linha, end);
		free(linha);
		free(end);
		free(var);
		free(init);
	}
	else if (!final)
	{
		*line = ft_strjoin(init, end);
		free(end);
		free(init);
	}
}

t_bool	ft_has_dollar(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	ft_var_expansion(char **line)
{
	char	*init;
	char	*var;
	char	*end;

	ft_parse_and_extract(line, &init, &var, &end);
	if (ft_has_dollar(*line))
	{
		ft_expand_and_manage(line, init, var, end);
		return (ft_var_expansion(line));
	}
	return (FALSE);
}
