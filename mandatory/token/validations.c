/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:30:22 by matesant          #+#    #+#             */
/*   Updated: 2024/03/08 11:44:04 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_spaces(char **str)
{
	char	*start;
	char	*end;

	start = *str;
	end = *str + ft_strlen(*str);
	while (ft_isspace(*start))
		start++;
	while (end > start && ft_isspace(*end))
		end--;
	(*end) = '\0';
	ft_memmove(*str, start, end - start + 2);
}
void lalalal