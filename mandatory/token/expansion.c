/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:35:49 by matesant          #+#    #+#             */
/*   Updated: 2024/03/19 15:36:08 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_and_extract(t_exp *exp)
{
	int		j;
	char	*line;

	line = exp->line;
	j = 0;
	exp->init = ft_substr(line, 0, ft_strchr(line, '$') - line);
	line = ft_strchr(line, '$');
	if (line)
		line++;
	while (line[j] && ft_isalnum(line[j]) == 1)
		j++;
	exp->var = ft_substr(line, 0, j);
	line += j;
	exp->end = ft_substr(line, 0, ft_strlen(line));
	printf("var: %s\n", exp->var);
	free(exp->line);
}

void	ft_expand_and_manage(t_exp *exp)
{
	char	*line;
	char	*result;
	char	*var;

	result = NULL;
	var = ft_strdup(getenv(exp->var));
	if (!exp->var)
		line = ft_strjoin(exp->init, exp->end);
	if (exp->var)
	{
		line = ft_strjoin(exp->init, var);
		result = ft_strjoin(line, exp->end);
	}
	free(line);
	free(exp->init);
	free(exp->var);
	free(exp->end);
	free(var);
	free(ft_get_shell()->user_input);
	ft_get_shell()->user_input = ft_strdup(result);
	if (result)
		free(result);
}

t_bool	ft_has_dollar(t_exp *exp)
{
	int	i;

	i = 0;
	while (exp->line[i])
	{
		if (exp->line[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	ft_var_expansion(void)
{
	static t_exp	exp;

	exp.line = ft_strdup(ft_get_shell()->user_input);
	ft_parse_and_extract(&exp);
	// if (ft_has_dollar(&exp))
	//{
	ft_expand_and_manage(&exp);
	//	return (ft_var_expansion());
	//}
	return (FALSE);
}
