/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:06:17 by matesant          #+#    #+#             */
/*   Updated: 2024/03/29 21:34:10 by matesant         ###   ########.fr       */
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
	free(shell->user_input);
	ft_free_tokens(shell);
	free_cmd_list(&shell->commands);
	ft_garbage_clear(&shell->gc);
}
