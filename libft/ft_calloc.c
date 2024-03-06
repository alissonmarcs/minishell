/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:09:16 by matesant          #+#    #+#             */
/*   Updated: 2023/11/13 19:19:14 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memoalloc;
	size_t	full_size;

	full_size = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (full_size > 2147483647 || full_size / nmemb != size)
		return (NULL);
	memoalloc = (void *)malloc(full_size);
	if (memoalloc == NULL)
		return (NULL);
	ft_bzero(memoalloc, full_size);
	return (memoalloc);
}
