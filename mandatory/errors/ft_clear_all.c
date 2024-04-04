/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:06:17 by matesant          #+#    #+#             */
/*   Updated: 2024/04/04 15:18:24 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_all(t_minishell *shell)
{
	free(shell->user_input);
	ft_free_tokens(shell);
	free_cmd_list(&shell->commands);
	ft_free_env(shell);
	ft_delete_matrice(shell->env);
	ft_garbage_clear(&shell->gc);
}

void	ft_clear(t_minishell *shell)
{
	if (shell->user_input)
		free(shell->user_input);
	ft_free_tokens(shell);
	free_cmd_list(&shell->commands);
	ft_garbage_clear(&shell->gc);
}
