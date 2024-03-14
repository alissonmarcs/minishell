/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:36:10 by matesant          #+#    #+#             */
/*   Updated: 2024/03/14 17:04:48 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*ft_get_shell(void)
{
	static t_minishell	shell;

	return (&shell);
}

void	ft_process(t_minishell *shell)
{
	if (ft_tokenize(shell))
		return ;
	ft_print_stack(shell->tokens);
	populate_command_list(shell);
	print_cmd_list(shell->commands);
}

void	ft_loop(void)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	while (1)
	{
		ft_receive_signal();
		shell->user_input = readline(PROMPT);
		if (!shell->user_input)
			break ;
		if (shell->user_input[0] == '\0')
		{
			free(shell->user_input);
			continue ;
		}
		add_history(shell->user_input);
		ft_process(shell);
		free(shell->user_input);
		ft_free_list(shell);
		free_cmd_list(&shell->commands);
	}
	rl_clear_history();
}

int	main(void)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	// signa
	ft_bzero(shell, sizeof(t_minishell));
	ft_loop();
	return (0);
}
