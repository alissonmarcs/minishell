/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:35:49 by matesant          #+#    #+#             */
/*   Updated: 2024/03/21 17:50:48 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_var(char *str)
{
	int		j;
	char	*line;

	j = 1;
	line = str;
	line = ft_strchr(line, '$');
	if (!line)
		return (NULL);
	while (line[j] && ft_isalnum(line[j]))
		j++;
	return (ft_substr(line, 0, j));
}

t_bool	ft_dollars_in_my_pocket(char *input, t_exp *exp)
{
	static int	status;

	while (input[exp->i])
	{
		status = ft_quotes_status(input[exp->i], status);
		//if (input[i] == '$' && input[i + 1] == '$' && (status == 0
		//		|| status == 1))
		//{
		//	ft_dollar_treatment(input, exp);
		//	i++;
		//	return (TRUE);
		//}
		if (input[exp->i] == '$' && (status == 0 || status == 1)
			&& ft_isalpha(input[exp->i + 1]) == 1)
			return (TRUE);
		exp->i++;
	}
	return (FALSE);
}

t_bool	ft_var_expansion(void)
{
	static t_exp	exp;
	t_token			*curr;

	curr = ft_get_shell()->tokens;
	while (curr && curr->type != END)
	{
		if (ft_dollars_in_my_pocket(curr->str, &exp))
		{
			exp.var = ft_find_var(curr->str);
			curr->str = replace_first_occurency(exp.var, ft_getenv(exp.var + 1),
				curr->str);
			curr->type = VAR;
			continue ;
		}
		ft_replace_teemo(curr, ft_get_shell()->teemo);
		exp = (t_exp){NULL, 0};
		curr = curr->next;
	}
	return (FALSE);
}
