/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:30:22 by matesant          #+#    #+#             */
/*   Updated: 2024/03/08 11:14:08 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_spaces(char **str)
{
	int	end;

	end = ft_strlen(*str);
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
	while ((*str)[end - 1] == ' ' || ((*str)[end - 1] >= 9 && (*str)[end
			- 1] <= 13))
		end--;
	(*str)[end] = '\0';
}
