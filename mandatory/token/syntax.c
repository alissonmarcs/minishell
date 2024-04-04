/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:57:12 by matesant          #+#    #+#             */
/*   Updated: 2024/04/04 14:30:11 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_eof(t_token *curr, int type)
{
	if (type == PIPE && curr->next->type == PIPE)
		return ("syntax error near unexpected token `|'");
	else if (type == PIPE && (!curr->prev))
		return ("syntax error near unexpected token `|'");
	else if (type == PIPE && (!curr->next || curr->next->type == END))
		return ("syntax error near unexpected token `|'");
	else if (type == HERE_DOC && (!curr->next || curr->next->type == END))
		return ("unexpected end of file");
	else if (type == APPEND && (!curr->next || curr->next->type == END))
		return ("unexpected end of file");
	else if (type == INPUT && (!curr->next || curr->next->type == END))
		return ("unexpected end of file");
	else if (type == TRUNC && (!curr->next || curr->next->type == END))
		return ("syntax error near unexpected token `newline'");
	return (NULL);
}

char	*ft_check_syntax(t_token *tokens)
{
	t_token	*curr;
	int		type;

	curr = tokens;
	while (curr)
	{
		type = curr->type;
		if ((type == TRUNC && (curr->next->type != WORD)
				&& (curr->next->type != END)))
			return ("syntax error near unexpected token `>'");
		else if ((type == APPEND && (curr->next->type != WORD)
				&& (curr->next->type != END)))
			return ("syntax error near unexpected token `>>'");
		else if ((type == INPUT && (curr->next->type != WORD))
			&& (curr->next->type != END))
			return ("syntax error near unexpected token `<'");
		else if ((type == HERE_DOC && (curr->next->type != WORD)
				&& (curr->next->type != END)))
			return ("syntax error near unexpected token `<<'");
		if (ft_check_eof(curr, type))
			return (ft_check_eof(curr, type));
		curr = curr->next;
	}
	return (NULL);
}
