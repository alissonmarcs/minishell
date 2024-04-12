/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:36:10 by matesant          #+#    #+#             */
/*   Updated: 2024/04/11 13:13:29 by matesant         ###   ########.fr       */
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
	if (!check_here_docs(shell))
		return ;
	populate_command_list(shell);
	executor(shell);
}

void	ft_loop(void)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	while (TRUE)
	{
		ft_receive_signal();
		shell->user_input = readline(YELLOW "CarlitoShell$ " RESET);
		if (!shell->user_input)
			break ;
		add_history(shell->user_input);
		if (shell->user_input[0] == '\0')
		{
			free(shell->user_input);
			continue ;
		}
		ft_process(shell);
		ft_clear(shell);
		shell->heredocs = NULL;
	}
	ft_free_env(shell);
	rl_clear_history();
}

void	copy_standard_fds(t_minishell *shell)
{
	shell->standard_fds[0] = dup(STDIN_FILENO);
	shell->standard_fds[1] = dup(STDOUT_FILENO);
}

int	main(void)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	copy_standard_fds(shell);
	ft_clone_env(shell);
	shell->teemo = -1;
	ft_loop();
	ft_delete_matrice(shell->env);
	close(shell->standard_fds[0]);
	close(shell->standard_fds[1]);
	exit(ft_get_shell()->exit_status);
	return (0);
}
