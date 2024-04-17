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

	new = ft_calloc(1, sizeof(t_gc));
	new->content = content;
	new->next = ft_get_shell()->gc;
	ft_get_shell()->gc = new;
}

void	ft_garbage_clear(t_gc **garbage)
{
	t_gc	*current;
	t_gc	*next;

	current = *garbage;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*garbage = NULL;
}
