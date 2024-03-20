/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:35:49 by matesant          #+#    #+#             */
/*   Updated: 2024/03/20 18:21:35 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_and_extract(t_exp *exp)
{
	int		j;
	char	*line;

	j = 0;
	if (exp->line[0] == '$' && exp->line[1] == '\0')
	{
		exp->var = ft_strdup("$");
		return ;
	}
	line = exp->line;
	exp->init = ft_substr(line, 0, ft_strchr(line, '$') - line);
	line = ft_strchr(line, '$');
	if (!line)
		return ;
	if (line)
		line++;
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

char	*ft_expand_and_manage(t_exp *exp)
{
	char	*line;
	char	*result;
	char	*var;

	result = NULL;
	line = NULL;
	var = NULL;
	var = ft_getenv(exp->var);
	line = ft_strjoin(exp->init, var);
	result = ft_strjoin(line, exp->end);
	line = NULL;
	ft_free((void **)&exp->var);
	return (result);
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
	static int	status;

	while (input[exp->i])
	{
		status = ft_quotes_status(input[exp->i], status);
		if (input[exp->i] == '$' && input[exp->i + 1] == '$' && (status == 0
				|| status == 1))
		{
			exp->i += 2;
			return (TRUE);
		}
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
	t_token			*curr;

	shell = ft_get_shell();
	curr = shell->tokens;
	while (curr)
	{
		if (ft_dollars_in_my_pocket(curr->str, &exp))
		{
			exp.line = ft_strdup(curr->str);
			ft_parse_and_extract(&exp);
			if (curr->str)
			{
				free(curr->str);
				curr->str = NULL;
			}
			curr->str = ft_expand_and_manage(&exp);
			continue ;
		}
		exp = (t_exp){0};
		curr = curr->next;
	}
	return (FALSE);
}
