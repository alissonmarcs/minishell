/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:06:17 by matesant          #+#    #+#             */
/*   Updated: 2024/03/26 16:10:52 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_all(t_minishell *shell)
{
	free(shell->user_input);
	ft_free_tokens(shell);
	free_cmd_list(&shell->commands);
}
