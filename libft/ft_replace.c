/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:54:59 by matesant          #+#    #+#             */
/*   Updated: 2024/04/12 17:12:02 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace(char *old, char *new, char *str, int *i)
{
	char	*result;
	char	*ptr;
	char	*igor;
	char	*klb;

	ptr = str;
    ptr += (*i);
	if (!ptr)
		return (str);
	igor = ft_substr(str, 0, ptr - str);
	klb = ft_strjoin(igor, new);
	ft_free((void *)new);
	new = NULL;
	ft_free((void *)igor);
	igor = ft_substr(str, ptr - str + ft_strlen(old), ft_strlen(str));
	ft_free((void *)str);
	ft_free((void *)old);
	old = NULL;
	result = ft_strjoin(klb, igor);
	ft_free((void *)igor);
	ft_free((void *)klb);
	return (result);
}
