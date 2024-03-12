/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:36:10 by matesant          #+#    #+#             */
/*   Updated: 2024/03/12 12:12:46 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*ft_get_shell(void)
{
	static t_minishell	shell;

	return (&shell);
}

void	ft_loop(void)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	while (1)
	{
		shell->user_input = readline(PROMPT);
		if (!shell->user_input)
			break ;
		add_history(shell->user_input);
		ft_tokenize(shell);
		free(shell->user_input);
		ft_print_stack(shell->tokens);
		populate_command_list(shell);
		print_cmd_list(shell->commands);
		ft_free_list(shell);
		free_cmd_list(&shell->commands);
	}
	rl_clear_history();
}

int	main(void)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	ft_bzero(shell, sizeof(t_minishell));
	ft_loop();
	return (0);
}
