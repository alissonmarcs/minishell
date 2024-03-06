/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 09:47:21 by matesant          #+#    #+#             */
/*   Updated: 2024/01/24 15:11:09 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
		{
			words++;
			while (*s != '\0' && *s != c)
				s++;
		}
	}
	return (words);
}

static void	ft_erase(char **array)
{
	int	count;

	count = 0;
	if (!array)
		return ;
	while (array[count])
	{
		if (array[count] != NULL)
		{
			free(array[count]);
			array[count] = NULL;
		}
		count++;
	}
	free(array);
}

static char	**ft_allocate(char **array, const char *s, char c)
{
	int		word_len;
	size_t	i;

	i = 0;
	while (*s)
	{
		word_len = 0;
		while (s[word_len] != c && s[word_len])
			word_len++;
		array[i] = (char *)ft_calloc((word_len + 1), sizeof(char));
		if (array[i] == NULL)
		{
			ft_erase(array);
			return (NULL);
		}
		ft_strlcpy(array[i], s, word_len + 1);
		i++;
		while (*s != c && *s)
			s++;
		while (*s == c && *s)
			s++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**array;

	if (!(s))
		return (NULL);
	words = ft_count_words(s, c);
	array = (char **)ft_calloc((words + 1), sizeof(char *));
	if (!(array))
		return (NULL);
	while (*s == c && *s)
		s++;
	return (ft_allocate(array, s, c));
}
