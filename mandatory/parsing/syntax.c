/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:57:12 by matesant          #+#    #+#             */
/*   Updated: 2024/03/08 19:34:45 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_syntax2(t_token *curr)
{
	if ((curr->type == HERE_DOC || curr->type == APPEND || curr->type == INPUT
			|| curr->type == HERE_DOC) && (curr->next->type == HERE_DOC))
		ft_error("syntax error near unexpected token `>'");
	else if (curr->type == HERE_DOC && (!curr->next || curr->next->type == END))
		ft_error("unexpected end of file");
	else if (curr->type == INPUT && (!curr->next || curr->next->type == END))
		ft_error("unexpected end of file");
	else if (curr->type == TRUNC && (!curr->next || curr->next->type == END))
		ft_error("unexpected end of file");
}

void	ft_check_syntax(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == PIPE && (!curr->next || curr->next->type == END))
			ft_error("unexpected end of file");
		else if (curr->type == PIPE && curr->next->type == PIPE)
			ft_error("syntax error near unexpected token `|'");
		else if ((curr->type == TRUNC || curr->type == APPEND
				|| curr->type == HERE_DOC || curr->type == INPUT)
			&& (curr->next->type == PIPE))
			ft_error("syntax error near unexpected token `|'");
		else if ((curr->type == TRUNC || curr->type == APPEND
				|| curr->type == INPUT || curr->type == HERE_DOC)
			&& (curr->next->type == TRUNC))
			ft_error("syntax error near unexpected token `>'");
		else if ((curr->type == INPUT || curr->type == APPEND
				|| curr->type == TRUNC || curr->type == HERE_DOC)
			&& (curr->next->type == INPUT))
			ft_error("syntax error near unexpected token `<'");
		else
			ft_check_syntax2(curr);
		curr = curr->next;
	}
}
