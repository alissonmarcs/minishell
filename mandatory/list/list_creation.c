/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:12:17 by matesant          #+#    #+#             */
/*   Updated: 2024/03/20 18:03:51 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_create_list(char *str, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		ft_error("malloc error");
	ft_bzero(new, sizeof(t_token));
	ft_clear_spaces(&str);
	new->str = ft_strdup(str);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	free(str);
	return (new);
}

void	ft_lstend(t_token **tokens, char *str, int type)
{
	t_token	*curr;

	if (!*tokens)
	{
		*tokens = ft_create_list(str, type);
		return ;
	}
	curr = *tokens;
	while (curr->next)
		curr = curr->next;
	curr->next = ft_create_list(str, type);
	if (!curr->next)
		ft_error("malloc error");
	curr->next->prev = curr;
}
