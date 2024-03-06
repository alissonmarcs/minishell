/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:10:29 by matesant          #+#    #+#             */
/*   Updated: 2023/11/13 19:12:12 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t			len;
	char			*nstr;

	len = ft_strlen(str) + 1;
	nstr = (char *)ft_calloc(len, sizeof(char));
	if (!nstr)
		return (NULL);
	ft_strlcpy(nstr, str, len);
	return (nstr);
}
