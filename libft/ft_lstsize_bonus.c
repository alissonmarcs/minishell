/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:59:21 by matesant          #+#    #+#             */
/*   Updated: 2024/03/28 16:26:01 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	items;

	if (lst == NULL)
		return (0);
	items = 1;
	while (lst->next != NULL)
	{
		items++;
		lst = lst->next;
	}
	return (items);
}
