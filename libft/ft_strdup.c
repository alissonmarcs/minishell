/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:10:29 by matesant          #+#    #+#             */
/*   Updated: 2024/03/28 18:48:54 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	int		i;
	char	*nstr;

	i = 0;
	len = ft_strlen(str) + 1;
	if (!str)
		return (NULL);
	nstr = (char *)ft_calloc(len, sizeof(char));
	if (!nstr)
		return (NULL);
	while (str[i] != '\0')
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}

char	*ft_nullstrdup(const char *str)
{
	size_t	len;
	int		i;
	char	*nstr;

	i = 0;
	len = ft_strlen(str) + 1;
	nstr = (char *)ft_calloc(len, sizeof(char));
	if (!nstr)
		return (NULL);
	if (!str)
		return (nstr);
	while (str[i])
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
