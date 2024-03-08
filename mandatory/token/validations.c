/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:30:22 by matesant          #+#    #+#             */
/*   Updated: 2024/03/08 12:30:35 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_spaces(char **str)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	end = ft_strlen(*str) - 1;
	while (ft_isspace((*str)[start]))
		start++;
	while (end >= start && ft_isspace((*str)[end]))
		end--;
	i = start;
	while (i <= end)
	{
		(*str)[i - start] = (*str)[i];
		i++;
	}
	(*str)[i - start] = '\0';
}

// void ft_skip_quotes()