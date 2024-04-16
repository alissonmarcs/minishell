/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:12:28 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/16 19:12:29 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_three(char *one, char *two, char *three, t_bool to_free)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(one, two);
	if (to_free)
	{
		free(one);
		free(two);
	}
	if (three)
	{
		joined = ft_strjoin(tmp, three);
		if (to_free)
			free(three);
		free(tmp);
		return (joined);
	}
	return (tmp);
}
