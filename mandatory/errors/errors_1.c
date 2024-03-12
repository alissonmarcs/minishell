/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:19:40 by matesant          #+#    #+#             */
/*   Updated: 2024/03/12 15:20:23 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_error(char *str)
{
	if (str != NULL)
	{
		ft_printf_fd(2, "%sminishell: %s%s\n", RED, str, RESET);
		ft_free_list(ft_get_shell());
		return (TRUE);
	}
	return (FALSE);
}

void	ft_free_list(t_minishell *shell)
{
	t_token	*tmp;

	while (shell->tokens)
	{
		tmp = shell->tokens;
		shell->tokens = shell->tokens->next;
		free(tmp->str);
		free(tmp);
	}
}
