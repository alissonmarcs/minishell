/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:35:49 by matesant          #+#    #+#             */
/*   Updated: 2024/03/19 19:21:18 by matesant         ###   ########.fr       */
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
	if (!line)
		return ;
	if (line)
		line++;
	while (line[j] && ft_isalnum(line[j]) == 1)
		j++;
	exp->var = ft_substr(line, 0, j);
	line += j;
	exp->end = ft_substr(line, 0, ft_strlen(line));
	free(exp->line);
	exp->line = NULL;
}

void	ft_expand_and_manage(t_exp *exp)
{
	char	*line;
	char	*result;
	char	*var;

	result = NULL;
	line = NULL;
	var = NULL;
	var = ft_strdup(getenv(exp->var));
	printf("var: %p\n", var);
	line = ft_strjoin(exp->init, var);
	result = ft_strjoin(line, exp->end);
	line = NULL;
	ft_free((void **)&exp->var);
	ft_get_shell()->user_input = result;
}

t_bool	ft_var_expansion(void)
{
	static t_exp	exp;
	t_minishell		*shell;

	exp.line = ft_strdup(ft_get_shell()->user_input);
	shell = ft_get_shell();
	if (ft_strchr(shell->user_input, '$'))
	{
		ft_parse_and_extract(&exp);
		if (ft_get_shell()->user_input)
		{
			free(ft_get_shell()->user_input);
			ft_get_shell()->user_input = NULL;
		}
		ft_expand_and_manage(&exp);
		return (ft_var_expansion());
	}
	free(exp.line);
	return (FALSE);
}
