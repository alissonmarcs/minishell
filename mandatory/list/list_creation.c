/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:12:17 by matesant          #+#    #+#             */
/*   Updated: 2024/03/05 19:26:50 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*ft_create_list(char *str)
{
	t_minishell	*new;

	new = malloc(sizeof(t_minishell));
	if (!new)
		ft_error("malloc error");
	ft_bzero(new, sizeof(t_minishell));
	new->token = str;
	new->next = NULL;
	return (new);
}
void	ft_lstend(t_minishell **tokens, char *str)
{
	t_minishell	*curr;

	if (!*tokens)
	{
		*tokens = ft_create_list(str);
		return ;
	}
	curr = *tokens;
	while (curr)
	{
		curr = curr->next;
	}
	curr->next = ft_create_list(str);
}
