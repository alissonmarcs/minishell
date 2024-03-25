/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:29:06 by matesant          #+#    #+#             */
/*   Updated: 2024/03/22 12:40:24 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rlstnew(t_gc **lst, void *content)
{
	t_gc	*new;

	new = malloc(sizeof(t_gc));
	if (!new)
		ft_error("malloc error");
	new->content = content;
	new->next = *lst;
	*lst = new;
}

void	ft_garbage_clear(t_gc **garbage)
{
	t_gc	*tmp;

	while (*garbage)
	{
		tmp = *garbage;
		*garbage = (*garbage)->next;
		if (tmp->content && *tmp->content)
			ft_free((void **)&tmp->content);
		if (tmp)
			ft_free((void **)&tmp);
	}
}
