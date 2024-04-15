/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:12:17 by matesant          #+#    #+#             */
/*   Updated: 2024/04/02 16:56:23 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_create_list(char *str, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		ft_error("malloc error", 900);
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
		ft_error("malloc error", 900);
	curr->next->prev = curr;
}

t_env	*ft_create_var_list(char *key, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	return (new);
}

void	ft_lstend_var(t_env **env_list, char *key, char *value, int equal)
{
	t_env	*curr;

	curr = *env_list;
	if (!*env_list)
	{
		*env_list = ft_create_var_list(key, value);
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = ft_create_var_list(key, value);
	curr->next->prev = curr;
	curr = curr->next;
	curr->equal = equal;
}
