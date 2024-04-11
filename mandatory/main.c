/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:36:10 by matesant          #+#    #+#             */
/*   Updated: 2024/04/09 17:09:58 by matesant         ###   ########.fr       */
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
	//print_cmd_list(shell->commands);
	if (ft_strcmp(shell->tokens->str, "cd") == 0)
	{
		ft_cd_builtin(shell->commands->argv);
		return ;
	}
	if (ft_strcmp(shell->tokens->str, "env") == 0)
	{
		ft_env_builtin(shell->commands->argv);
		return ;
	}
	if (ft_strcmp(shell->tokens->str, "exit") == 0)
		ft_exit(shell->commands->argv);
	else if (ft_strcmp(shell->tokens->str, "export") == 0)
	{
		ft_export(shell->commands->argv);
		return ;
	}
	else if (ft_strcmp(shell->tokens->str, "unset") == 0)
	{
		ft_unset(shell->commands->argv);
		return ;
	}
	else if (ft_strcmp(shell->tokens->str, "echo") == 0)
	{
		ft_echo_builtin(shell->commands->argv);
		return ;
	}
	else if (ft_strcmp(shell->tokens->str, "pwd") == 0)
	{
		ft_pwd_builtin(shell->commands->argv);
		return ;
	}
	executor(shell);
}

void	ft_loop(void)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	while (TRUE)
	{
		ft_receive_signal();
		shell->user_input = readline(YELLOW"CarlitoShell$ "RESET);
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

int	main(void)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	ft_clone_env(shell);
	shell->teemo = -1;
	ft_loop();
	ft_delete_matrice(shell->env);
	exit(ft_get_shell()->exit_status);
	return (0);
}
