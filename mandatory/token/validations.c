/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:30:22 by matesant          #+#    #+#             */
/*   Updated: 2024/03/08 15:21:00 by matesant         ###   ########.fr       */
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

void	ft_open_quotes(char *str)
{
	int	status;
	int	i;

	i = -1;
	status = 0;
	while (str[++i])
	{
		if (str[i] == '\"' && status == 0)
			status = 1;
		else if (str[i] == '\"' && status == 1)
			status = 0;
		else if (str[i] == '\'' && status == 0)
			status = 2;
		else if (str[i] == '\'' && status == 2)
			status = 0;
		if (str[i + 1] == '\0' && status != 0)
			ft_error("syntax error");
	}
}

void	ft_skip_quotes(char *str, unsigned long *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
	}
	else if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"')
			(*i)++;
	}
}
