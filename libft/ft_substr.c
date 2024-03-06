/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:14:59 by matesant          #+#    #+#             */
/*   Updated: 2024/02/08 16:08:49 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*subs;
	size_t	len_sub;

	i = 0;
	len_sub = ft_strlen(s);
	if (start >= len_sub)
		return (ft_strdup(""));
	if (len_sub - start < len)
		len = len_sub - start;
	subs = malloc((len + 1) * sizeof(char));
	if (!(subs))
		return (NULL);
	while (s[i + start] && (i < len))
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[len] = '\0';
	return (subs);
}
