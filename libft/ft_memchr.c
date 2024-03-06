/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:28:51 by matesant          #+#    #+#             */
/*   Updated: 2023/08/13 17:52:36 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	finder;
	unsigned int	i;

	ptr = (unsigned char *)s;
	finder = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == finder)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}
