/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:53:07 by matesant          #+#    #+#             */
/*   Updated: 2023/08/11 15:08:39 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t n)
{
	size_t	len;

	if (*substr == '\0')
		return ((char *)str);
	len = ft_strlen(substr);
	while (*str && n-- >= len)
	{
		if (ft_memcmp(str, substr, len) == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
