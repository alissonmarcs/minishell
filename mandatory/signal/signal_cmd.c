/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:09:53 by matesant          #+#    #+#             */
/*   Updated: 2024/04/12 12:11:15 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ctrl_c_cmd(int sig)
{
	(void)sig;
	ft_printf_fd(STDERR_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void sig_stop(int sig)
{
	(void)sig;
	ft_printf_fd(STDERR_FILENO, "\n");
	ft_printf_fd(STDERR_FILENO, "Quit (core dumped)\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void cmd_signal(void)
{
	signal(SIGINT, ctrl_c_cmd);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, sig_stop);
}
void	ctrl_c_heredoc(int sig)
{
	if (sig == SIGINT)
		clear_exit(ft_get_shell(), 130);
}


