/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:09:53 by matesant          #+#    #+#             */
/*   Updated: 2024/04/22 16:41:17 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_cmd(int sig)
{
	(void)sig;
	ft_printf_fd(STDERR_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sig_stop(int sig)
{
	(void)sig;
	ft_printf_fd(STDERR_FILENO, "\n");
	ft_printf_fd(STDERR_FILENO, "Quit (core dumped)\n");
	ft_get_shell()->exit_status = 131;
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handle_z(int sig)
{
	(void)sig;
	ft_printf_fd(STDERR_FILENO, "\n");
	ft_printf_fd(STDERR_FILENO, "Stopped\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	cmd_signal(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = handle_z;
	signal(SIGINT, ctrl_c_cmd);
	signal(SIGQUIT, sig_stop);
	sigaction(SIGTSTP, &act, NULL);
}

void	ctrl_c_heredoc(int sig)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	if (sig == SIGINT)
	{
		shell->exit_status = 130;
		clear_exit(shell, TRUE);
	}
}
