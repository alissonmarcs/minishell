/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:35:49 by matesant          #+#    #+#             */
/*   Updated: 2024/03/20 11:56:39 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_and_extract(t_exp *exp)
{
	int		j;
	char	*line;

	line = exp->line;
	j = 0;
	if (exp->i != 0)
		exp->init = ft_substr(line, 0, exp->i);
	line += exp->i + 1;
	if (!line)
		return ;
	while (line[j] && ft_isalnum(line[j]) == 1)
		j++;
	if (line[j] == '$')
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
	line = ft_strjoin(exp->init, var);
	result = ft_strjoin(line, exp->end);
	line = NULL;
	ft_free((void **)&exp->var);
	ft_get_shell()->user_input = result;
}

t_bool	ft_quotes_status(char c, int status)
{
	if (c == '\'' && status == 0)
		status = 2;
	else if (c == '\'' && status == 2)
		status = 0;
	else if (c == '\"' && status == 0)
		status = 1;
	else if (c == '\"' && status == 1)
		status = 0;
	return (status);
}

t_bool	ft_dollars_in_my_pocket(char *input, t_exp *exp)
{
	int	status;

	exp->i = 0;
	status = 0;
	while (input[exp->i])
	{
		status = ft_quotes_status(input[exp->i], status);
		if (input[exp->i] == '$' && (status == 0 || status == 1))
			return (TRUE);
		exp->i++;
	}
	return (FALSE);
}

t_bool	ft_var_expansion(void)
{
	static t_exp	exp;
	t_minishell		*shell;

	exp.line = ft_strdup(ft_get_shell()->user_input);
	shell = ft_get_shell();
	if (ft_dollars_in_my_pocket(shell->user_input, &exp))
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
