/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:12:38 by matesant          #+#    #+#             */
/*   Updated: 2024/04/16 17:12:41 by matesant         ###   ########.fr       */
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
