/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:29:06 by matesant          #+#    #+#             */
/*   Updated: 2024/03/28 12:38:55 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rlstnew(void *content)
{
	t_gc	*new;

	new = malloc(sizeof(t_gc));
	if (!new)
		ft_error("malloc error", 900);
	new->content = content;
	new->next = ft_get_shell()->gc;
	ft_get_shell()->gc = new;
}

void	ft_garbage_clear(t_gc **garbage)
{
	t_gc	*tmp;

	while (*garbage)
	{
		tmp = *garbage;
		*garbage = (*garbage)->next;
		if (tmp->content && *tmp->content)
			ft_free_ptr((void **)&tmp->content);
		if (tmp)
			ft_free_ptr((void **)&tmp);
	}
}
