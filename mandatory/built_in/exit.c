/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:36:00 by matesant          #+#    #+#             */
/*   Updated: 2024/04/09 17:07:54 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_exit_msg(char **argv, char *msg, char *arg, int ecode)
{
	if (arg)
	{
		ft_printf_fd(STDERR_FILENO, "exit\nminishell: %s: %s: %s\n", argv[0],
			arg, msg);
		ft_clear_all(ft_get_shell());
		exit(ecode);
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "exit\nminishell: %s: %s\n", argv[0], msg);
		ft_get_shell()->exit_status = ecode;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ft_check_max_min(char *arg)
{
	if ((ft_atol(arg) > 2147483647) || (ft_atol(arg) < -2147483648))
		return (TRUE);
	return (FALSE);
}

void	ft_exit(char **argv)
{
	if ((argv[1] && ft_has_alpha(argv[1])) || (ft_check_max_min(argv[1])))
		ft_exit_msg(argv, "numeric argument required", argv[1], 2);
	else if (ft_matrice_len(argv) > 2)
	{
		if (ft_exit_msg(argv, "too many arguments", NULL, 1))
			return ;
	}
	else if (argv[1])
		ft_get_shell()->exit_status = ft_atol(argv[1]);
	exit(ft_get_shell()->exit_status);
}
