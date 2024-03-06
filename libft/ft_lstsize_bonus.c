/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:59:21 by matesant          #+#    #+#             */
/*   Updated: 2023/08/07 10:18:30 by matesant         ###   ########.fr       */
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
