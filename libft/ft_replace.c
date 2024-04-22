/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:54:59 by matesant          #+#    #+#             */
/*   Updated: 2024/04/16 17:11:23 by matesant         ###   ########.fr       */
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
	free((void *)new);
	new = NULL;
	free((void *)igor);
	igor = ft_substr(str, ptr - str + ft_strlen(old), ft_strlen(str));
	free((void *)str);
	free((void *)old);
	old = NULL;
	result = ft_strjoin(klb, igor);
	free((void *)igor);
	free((void *)klb);
	return (result);
}
