/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:09:53 by matesant          #+#    #+#             */
/*   Updated: 2024/04/23 15:35:25 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_cmd(int sig)
{
	(void)sig;
	ft_get_shell()->exit_status = 130;
	ft_printf_fd(STDERR_FILENO, "\n");
}

void	sig_stop(int sig)
{
	(void)sig;
	ft_printf_fd(STDERR_FILENO, "\n");
	ft_printf_fd(STDERR_FILENO, "Quit (core dumped)\n");
	ft_get_shell()->exit_status = 131;
}

void	cmd_signal(void)
{
	signal(SIGINT, ctrl_c_cmd);
	signal(SIGQUIT, sig_stop);
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
