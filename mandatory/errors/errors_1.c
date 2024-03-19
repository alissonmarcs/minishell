/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:19:40 by matesant          #+#    #+#             */
/*   Updated: 2024/03/19 19:06:58 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_error(char *str)
{
	if (str != NULL)
	{
		ft_printf_fd(2, "%sminishell: %s%s\n", RED, str, RESET);
		ft_free_tokens(ft_get_shell());
		return (TRUE);
	}
	return (FALSE);
}

void	ft_free_tokens(t_minishell *shell)
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

void	ft_free_env(t_minishell *shell)
{
	t_env	*tmp;

	while (shell->env_list)
	{
		tmp = shell->env_list;
		shell->env_list = shell->env_list->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
