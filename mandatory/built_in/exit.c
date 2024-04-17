/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:36:00 by matesant          #+#    #+#             */
/*   Updated: 2024/04/16 18:00:10 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ft_exit_msg(char **argv, char *msg, char *arg, int ecode);
static t_bool	ft_check_max_min(char *arg);

void	ft_exit(char **argv)
{
	ft_get_shell()->exit_status = 0;
	if ((argv[1] && ft_has_alpha(argv[1])) || (ft_check_max_min(argv[1])))
		ft_exit_msg(argv, "numeric argument required", argv[1], 2);
	else if (ft_matrice_len(argv) > 2)
	{
		if (ft_exit_msg(argv, "too many arguments", NULL, 1))
			return ;
	}
	else if (argv[1])
		ft_get_shell()->exit_status = ft_atol(argv[1]);
	ft_putstr_fd("exit\n", 1);
	clear_exit(ft_get_shell(), TRUE);
}

static t_bool	ft_exit_msg(char **argv, char *msg, char *arg, int ecode)
{
	if (arg)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: %s: %s\n", argv[0],
			arg, msg);
		ft_get_shell()->exit_status = ecode;
		clear_exit(ft_get_shell(), TRUE);
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", argv[0], msg);
		ft_get_shell()->exit_status = ecode;
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	ft_check_max_min(char *arg)
{
	while (arg && *arg == '0')
		arg++;
	if (ft_strlen(arg) == 19 && ft_strcmp(arg, "9223372036854775807") > 0)
		return (TRUE);
	else if (ft_strlen(arg) == 20 && ft_strcmp(arg, "-9223372036854775808") > 0)
		return (TRUE);
	else if (ft_strlen(arg) > 20)
		return (TRUE);
	return (FALSE);
}


