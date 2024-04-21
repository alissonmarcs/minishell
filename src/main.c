/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:36:10 by matesant          #+#    #+#             */
/*   Updated: 2024/04/12 10:54:42 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_loop(void);
static void	ft_process(t_minishell *shell);

int	main(void)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	save_restore_input(0);
	copy_standard_fds(shell);
	ft_clone_env(shell);
	shell->teemo = -1;
	ft_loop();
	clear_exit(shell, TRUE);
}

t_minishell	*ft_get_shell(void)
{
	static t_minishell	shell;

	return (&shell);
}

void	save_restore_input(int fd)
{
	static struct termios	tty;

	if (!fd)
		tcgetattr(STDIN_FILENO, &tty);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

static void	ft_loop(void)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	while (TRUE)
	{
		save_restore_input(1);
		ft_receive_signal();
		shell->user_input = readline(YELLOW "CarlitoShell$ " RESET);
		if (!shell->user_input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		add_history(shell->user_input);
		if (shell->user_input[0] == '\0')
		{
			free(shell->user_input);
			continue ;
		}
		shell->env = list_to_array(shell->env_list);
		ft_process(shell);
		clear_exit(shell, FALSE);
	}
	ft_free_env(shell);
	rl_clear_history();
}

static void	ft_process(t_minishell *shell)
{
	if (ft_tokenize(shell))
		return ;
	if (!check_here_docs(shell))
		return ;
	populate_command_list(shell);
	set_commands_with_no_argv(shell->commands);
	executor(shell);
}
