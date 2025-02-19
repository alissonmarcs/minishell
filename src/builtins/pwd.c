/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:31:34 by matesant          #+#    #+#             */
/*   Updated: 2024/04/16 17:42:26 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd_builtin(char **argv)
{
	char	*pwd;

	if (argv[1])
	{
		if (argv[1][0] == '-')
		{
			ft_printf_fd(STDERR_FILENO, "pwd: %s: invalid option\n", argv[1]);
			return ;
		}
	}
	ft_get_shell()->exit_status = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		ft_get_shell()->exit_status = 1;
		return ;
	}
	ft_printf_fd(STDOUT_FILENO, "%s\n", pwd);
	free(pwd);
}
