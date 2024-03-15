/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:15:46 by matesant          #+#    #+#             */
/*   Updated: 2024/03/15 16:53:54 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_open_quotes(char *str)
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
			return (TRUE);
	}
	return (FALSE);
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

t_bool	ft_set_status(char str)
{
	static int	status;

	if (str != '\"' && str != '\'')
		return (FALSE);
	else if (str == '\"' && status == 0)
	{
		status = 1;
		return (TRUE);
	}
	else if (str == '\"' && status == 1)
	{
		status = 0;
		return (TRUE);
	}
	else if (str == '\'' && status == 0)
	{
		status = 2;
		return (TRUE);
	}
	else if (str == '\'' && status == 2)
	{
		status = 0;
		return (TRUE);
	}
	return (FALSE);
}

void	ft_quotes_treatment(char **str)
{
	int		i;
	int		j;
	char	*new;
	int		status;
	char	*tmp;

	i = -1;
	j = 0;
	status = 0;
	tmp = *str;
	new = malloc(sizeof(char) * ft_strlen(*str) + 1);
	if (!new)
		ft_error("malloc error");
	while (tmp[++i])
	{
		if (ft_set_status(tmp[i]))
			continue ;
		new[j] = (tmp[i]);
		j++;
	}
	new[j] = '\0';
	free(*str);
	*str = new;
}
