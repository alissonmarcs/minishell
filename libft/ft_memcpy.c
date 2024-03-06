/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:39:42 by matesant          #+#    #+#             */
/*   Updated: 2023/08/11 19:33:49 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*c;
	char			*d;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	c = (char *)dest;
	d = (char *)src;
	while (i < n)
	{
		c[i] = d[i];
		i++;
	}
	return (dest);
}
