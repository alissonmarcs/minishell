/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_token_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:48:30 by matesant          #+#    #+#             */
/*   Updated: 2024/04/01 00:58:01 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool ft_pre_token_err(char *line)
{
	if (ft_only_spaces(line))
		return (TRUE);
	if (ft_open_quotes(line))
	{
		ft_error("Open quotes", 2);
		return (TRUE);
	}
	if (ft_error(ft_forbidden_separators(line), 2))
		return (TRUE);
	return (FALSE);
}