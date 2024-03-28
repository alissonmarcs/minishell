/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:36:10 by matesant          #+#    #+#             */
/*   Updated: 2024/03/28 16:27:58 by matesant         ###   ########.fr       */
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
	populate_command_list(shell);
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
	if (ft_strcmp(shell->tokens->str, "export") == 0)
	{
		ft_export(shell->commands->argv);
		return ;
	}
	executor(shell);
}

void	ft_loop(void)
{
	t_minishell	*shell;
	char		*line;

	shell = ft_get_shell();
	while (1)
	{
		ft_receive_signal();
		line = readline(PROMPT);
		if (!line)
			break ;
		shell->user_input = ft_strdup(line);
		add_history(line);
		free(line);
		if (shell->user_input[0] == '\0')
		{
			free(shell->user_input);
			continue ;
		}
		ft_process(shell);
		ft_clear(shell);
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
	return (0);
}
