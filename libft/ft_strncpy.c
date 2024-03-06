/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:30:32 by matesant          #+#    #+#             */
/*   Updated: 2023/11/27 17:02:59 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strncpy(char *dest, const char *src, size_t n)
{
	unsigned int	ind;

	ind = 0;
	while (src[ind] != '\0' && ind < n - 1)
	{
		dest[ind] = src[ind];
		ind++;
	}
	dest[ind] = '\0';
}
