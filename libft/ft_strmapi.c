/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:53:53 by matesant          #+#    #+#             */
/*   Updated: 2023/08/13 15:26:00 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*newstrit;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	newstrit = malloc((len + 1) * sizeof(char));
	if (newstrit == NULL)
		return (NULL);
	newstrit[len] = '\0';
	while (len > 0)
	{
		newstrit[len - 1] = f(len - 1, s[len - 1]);
		len--;
	}
	return (newstrit);
}
