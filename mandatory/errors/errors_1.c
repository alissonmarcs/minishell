/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:19:40 by matesant          #+#    #+#             */
/*   Updated: 2024/04/09 17:17:20 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_invalid_key(char *key, char *value)
{
	if (value)
		ft_printf_fd(STDERR_FILENO,
			"minishell: export: `%s=%s': not a valid identifier%s\n", key,
			value);
	else
		ft_printf_fd(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n", key);
	ft_get_shell()->exit_status = 1;
}

t_bool	ft_error(char *str, int exit_code)
{
	if (str != NULL)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s\n", str);
		ft_get_shell()->exit_status = exit_code;
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
		ft_free_ptr((void **)&tmp->value);
		free(tmp);
	}
}
