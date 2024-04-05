/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:31:34 by matesant          #+#    #+#             */
/*   Updated: 2024/04/04 18:12:53 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd_builtin(char **argv)
{
	char	*pwd;

	(void)argv;
	pwd = getcwd(NULL, 0);
	ft_printf_fd(STDOUT_FILENO, "%s\n", pwd);
	free(pwd);
}
