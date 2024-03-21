/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:29:06 by matesant          #+#    #+#             */
/*   Updated: 2024/03/21 16:53:04 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_garbage(void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	new->next = ft_get_shell()->gc;
}

void	ft_garbage_clear(t_list **garbage)
{
	t_list	*tmp;

	while (*garbage)
	{
		tmp = *garbage;
		*garbage = (*garbage)->next;
		if (tmp->content)
			ft_free((void **)&tmp->content);
		if (tmp)
			ft_free((void **)&tmp);
	}
}
