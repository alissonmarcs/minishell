/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:57:12 by matesant          #+#    #+#             */
/*   Updated: 2024/03/12 11:43:58 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_syntax2(t_token *curr, int type)
{
	if ((type == HERE_DOC || type == APPEND || type == INPUT
			|| type == TRUNC) && (curr->next->type == HERE_DOC))
		ft_error("syntax error near unexpected token `<<'");
	else if ((type == APPEND || type == HERE_DOC || type == INPUT
			|| type == TRUNC) && (curr->next->type == APPEND))
		ft_error("syntax error near unexpected token `>>'");
	else if (type == HERE_DOC && (!curr->next || curr->next->type == END))
		ft_error("unexpected end of file");
	else if (type == APPEND && (!curr->next || curr->next->type == END))
		ft_error("unexpected end of file");
	else if (type == INPUT && (!curr->next || curr->next->type == END))
		ft_error("unexpected end of file");
	else if (type == TRUNC && (!curr->next || curr->next->type == END))
		ft_error("syntax error near unexpected token `newline'");
	else if ((type == INPUT || type == APPEND || type == TRUNC
			|| type == HERE_DOC) && (curr->next->type == INPUT))
		ft_error("syntax error near unexpected token `<'");
}

void	ft_check_syntax(t_token *tokens)
{
	t_token	*curr;
	int		type;

	curr = tokens;
	while (curr)
	{
		type = curr->type;
		if (type == PIPE && (!curr->prev))
			ft_error("syntax error near unexpected token `|'");
		else if (type == PIPE && (!curr->next || curr->next->type == END))
			ft_error("unexpected end of file");
		else if (type == PIPE && curr->next->type == PIPE)
			ft_error("syntax error near unexpected token `|'");
		else if ((type == TRUNC || type == APPEND || type == HERE_DOC
				|| type == INPUT) && (curr->next->type == PIPE))
			ft_error("syntax error near unexpected token `|'");
		else if ((type == TRUNC || type == APPEND || type == INPUT
				|| type == HERE_DOC) && (curr->next->type == TRUNC))
			ft_error("syntax error near unexpected token `>'");
		else
			ft_check_syntax2(curr, type);
		curr = curr->next;
	}
}
