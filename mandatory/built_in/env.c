/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:38:01 by matesant          #+#    #+#             */
/*   Updated: 2024/04/10 13:54:27 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_builtin(char **argv)
{
	t_env	*env;

	ft_get_shell()->exit_status = 0;
	env = ft_get_shell()->env_list;
	while (env)
	{
		if (ft_matrice_len(argv) > 1)
		{
			ft_printf_fd(STDERR_FILENO, "env: %s: No such file or directory\n",
				argv[1]);
			ft_get_shell()->exit_status = 127;
			return ;
		}
		if (env->value)
			ft_printf_fd(STDOUT_FILENO, "%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
