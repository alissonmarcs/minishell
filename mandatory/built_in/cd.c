/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:57:33 by matesant          #+#    #+#             */
/*   Updated: 2024/03/27 17:14:28 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_env(void)
{
	char	*oldpwd;
	char	*pwd;
	t_env	*cur;

	cur = ft_get_shell()->env_list;
	oldpwd = ft_getenv("PWD");
	pwd = getcwd(NULL, 0);
	while (cur)
	{
		if (!ft_strncmp(cur->key, "OLDPWD", 6))
		{
			free(cur->value);
			cur->value = ft_strdup(oldpwd);
		}
		if (!ft_strncmp(cur->key, "PWD", 3))
		{
			free(cur->value);
			cur->value = ft_strdup(pwd);
		}
		cur = cur->next;
	}
}

void	ft_chdir(char *path)
{
	if (!chdir(path))
	{
		ft_set_env();
	}
	else
	{
		ft_error("cd: no such file or directory", 1);
		return ;
	}
}

void	ft_cd_builtin(char **argv)
{
	char	*path;

	if (!argv || !argv[1] || !argv[1][0] || !ft_strncmp(argv[1], " ", 1)
		|| !ft_strncmp(argv[1], "--", 3) || !ft_strncmp(argv[1], "~", 2))
	{
		path = ft_getenv("HOME");
		if (!path)
		{
			ft_error("cd: HOME not set", 1);
			return ;
		}
	}
	else
		path = argv[1];
	ft_chdir(path);
}
