/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_treatments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:55:08 by matesant          #+#    #+#             */
/*   Updated: 2024/04/05 15:17:50 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_replace_teemo(t_token *curr, char c, int *i, int *status)
{
	int	j;

	j = 0;
	while (curr->str[j])
	{
		if (curr->str[j] == c)
			curr->str[j] = '$';
		j++;
	}
	(*i) = 0;
	(*status) = 0;
}
