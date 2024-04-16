/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:51:04 by matesant          #+#    #+#             */
/*   Updated: 2024/04/16 17:10:29 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset_promp(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_receive_signal(void)
{
	struct sigaction	act;
	struct sigaction	ign;
	struct sigaction	stp;

	ft_memset(&act, 0, sizeof(act));
	ft_memset(&ign, 0, sizeof(act));
	ft_memset(&stp, 0, sizeof(act));
	act.sa_sigaction = ft_reset_promp;
	ign.sa_handler = SIG_IGN;
	stp.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &ign, NULL);
	sigaction(SIGTSTP, &stp, NULL);
}
