/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:57:33 by matesant          #+#    #+#             */
/*   Updated: 2024/04/11 13:11:52 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_oldpwd_exist(t_env *cur)
{
	if (!ft_strncmp(cur->key, "OLDPWD", 6))
		return ;
	else
		ft_lstend_var(&ft_get_shell()->env_list, "OLDPWD", "", 0);
}

void	ft_set_env(void)
{
	char	*oldpwd;
	char	*pwd;
	t_env	*cur;

	cur = ft_get_shell()->env_list;
	oldpwd = ft_getenv("PWD");
	pwd = getcwd(NULL, 0);
	ft_oldpwd_exist(cur);
	while (cur)
	{
		if (!ft_strncmp(cur->key, "OLDPWD", 6))
		{
			free(cur->value);
			cur->value = ft_strdup(oldpwd);
			ft_free_ptr((void **)&oldpwd);
		}
		if (!ft_strncmp(cur->key, "PWD", 3))
		{
			free(cur->value);
			cur->value = ft_strdup(pwd);
			free(pwd);
			pwd = NULL;
		}
		cur = cur->next;
	}
}

char	*ft_basic_errors(char **path, char **argv)
{
	if (ft_matrice_len(argv) > 2)
		return ("cd: too many arguments");
	else if (!ft_strcmp(argv[1], "-"))
	{
		ft_rlstnew(*path = ft_getenv("OLDPWD"));
		if (!path || *path[0] == '\0')
			return ("cd: OLDPWD not set");
	}
	else
		*path = argv[1];
	return (NULL);
}

t_bool	ft_isdir(char *path)
{
	struct stat	statbuf;

	if (access(path, F_OK) == -1)
	{
		ft_error("cd: No such file or directory", 1);
		return (FALSE);
	}
	if (lstat(path, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
			return (TRUE);
		else
		{
			ft_error("cd: not a directory", 1);
			return (FALSE);
		}
	}
	return (FALSE);
}

void	ft_cd_builtin(char **argv)
{
	char	*path;

	ft_get_shell()->exit_status = 0;
	if (ft_error(ft_basic_errors(&path, argv), 1))
		return ;
	else if (!argv || !argv[1] || !argv[1][0] || !ft_strcmp(argv[1], " ")
		|| !ft_strcmp(argv[1], "--") || !ft_strcmp(argv[1], "~"))
	{
		ft_rlstnew(path = ft_getenv("HOME"));
		if (!path)
		{
			ft_error("cd: HOME not set", 1);
			return ;
		}
	}
	if (ft_isdir(path))
	{
		if (!chdir(path))
			ft_set_env();
		else
			ft_error("cd: no such file or directory", 1);
	}
}
