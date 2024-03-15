/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:57:12 by matesant          #+#    #+#             */
/*   Updated: 2024/03/12 15:24:05 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_syntax2(t_token *curr, int type)
{
	if ((type == HERE_DOC || type == APPEND || type == INPUT || type == TRUNC)
		&& (curr->next->type == HERE_DOC))
		return ("syntax error near unexpected token `<<'");
	else if ((type == APPEND || type == HERE_DOC || type == INPUT
			|| type == TRUNC) && (curr->next->type == APPEND))
		return ("syntax error near unexpected token `>>'");
	else if (type == HERE_DOC && (!curr->next || curr->next->type == END))
		return ("unexpected end of file");
	else if (type == APPEND && (!curr->next || curr->next->type == END))
		return ("unexpected end of file");
	else if (type == INPUT && (!curr->next || curr->next->type == END))
		return ("unexpected end of file");
	else if (type == TRUNC && (!curr->next || curr->next->type == END))
		return ("syntax error near unexpected token `newline'");
	else if ((type == INPUT || type == APPEND || type == TRUNC
			|| type == HERE_DOC) && (curr->next->type == INPUT))
		return ("syntax error near unexpected token `<'");
	else if ((type == TRUNC || type == APPEND || type == INPUT
			|| type == HERE_DOC) && (curr->next->type == TRUNC))
		return ("syntax error near unexpected token `>'");
	return (NULL);
}

char	*ft_check_syntax(t_token *tokens)
{
	t_token	*curr;
	char	*error;
	int		type;

	curr = tokens;
	error = NULL;
	while (curr)
	{
		type = curr->type;
		if (type == PIPE && (!curr->prev))
			return ("syntax error near unexpected token `|'");
		else if (type == PIPE && (!curr->next || curr->next->type == END))
			return ("syntax error near unexpected token `|'");
		else if (type == PIPE && curr->next->type == PIPE)
			return ("syntax error near unexpected token `|'");
		else if ((type == TRUNC || type == APPEND || type == HERE_DOC
				|| type == INPUT) && (curr->next->type == PIPE))
			return ("syntax error near unexpected token `|'");
		error = ft_check_syntax2(curr, type);
		if (error)
			return (error);
		curr = curr->next;
	}
	return (NULL);
}
