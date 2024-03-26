/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_treatments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:55:08 by matesant          #+#    #+#             */
/*   Updated: 2024/03/26 13:31:14 by matesant         ###   ########.fr       */
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

void	ft_replace_teemo(t_token *curr, char c)
{
	int	i;

	i = 0;
	while (curr->str[i])
	{
		if (curr->str[i] == c)
			curr->str[i] = '$';
		i++;
	}
}
