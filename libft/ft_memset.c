/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 08:22:03 by matesant          #+#    #+#             */
/*   Updated: 2023/08/11 19:36:48 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned int	ind;
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	ind = 0;
	while (ind < n)
	{
		ptr[ind] = c;
		ind++;
	}
	return (str);
}
