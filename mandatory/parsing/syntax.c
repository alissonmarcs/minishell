/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:57:12 by matesant          #+#    #+#             */
/*   Updated: 2024/03/08 18:02:37 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_syntax(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == PIPE && !curr->next)
			ft_error("unexpected end of file");
		else if (curr->type == PIPE && curr->next->type == PIPE)
			ft_error("syntax error near unexpected token '|'");
		curr = curr->next;
	}
}
