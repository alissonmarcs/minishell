/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:35:49 by matesant          #+#    #+#             */
/*   Updated: 2024/03/15 11:40:08 by matesant         ###   ########.fr       */
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
	while ((*line)[i + j] && ft_is_separator(&(*line)[i + j]) == 0)
		j++;
	*end = ft_substr(*line, i + j, ft_strlen(*line) - (i + j));
	*var = ft_substr(*line, i + 1, j - 1);
}

t_bool	ft_expand_and_manage(char **line, char *init, char *var, char *end)
{
	char	*final;
	char	*linha;

	final = getenv(var);
	if (final)
	{
		free(*line);
		*line = NULL;
		linha = ft_strjoin(init, final);
		*line = ft_strjoin(linha, end);
		free(linha);
	}
	free(end);
	free(var);
	free(init);
	return (FALSE);
}

t_bool	ft_var_expansion(char **line)
{
	char	*init;
	char	*var;
	char	*end;

	ft_parse_and_extract(line, &init, &var, &end);
	return (ft_expand_and_manage(line, init, var, end));
}
