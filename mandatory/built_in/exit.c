/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:36:00 by matesant          #+#    #+#             */
/*   Updated: 2024/03/30 23:40:21 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool ft_exit_msg(char **argv, char *msg, char *arg, int ecode)
{
	if (arg)
	{
		ft_printf_fd(STDERR_FILENO, "exit\n%sminishell: %s: %s: %s%s\n", RED, argv[0], arg, msg, RESET);
		ft_clear_all(ft_get_shell());
		exit(ecode);
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "exit\n%sminishell: %s: %s%s\n", RED, argv[0], msg, RESET);
		ft_get_shell()->exit_status = ecode;
		return (TRUE);
	}
	return (FALSE);
}


void	ft_exit(char **argv)
{
	if (argv[1] && ft_isalpha(argv[1][0]))
		ft_exit_msg(argv, "numeric argument required", argv[1], 2);
	if (ft_matrice_len(argv) > 2)
		if(ft_exit_msg(argv, "too many arguments", NULL, 1))
			return ;
	if (argv[1])
		ft_get_shell()->exit_status = ft_atoi(argv[1]);
	exit(ft_get_shell()->exit_status);
}
