/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:56:42 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/16 18:56:43 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(void)
{
	int unsigned	i;
	char			**paths;
	char			*path;
	char			*to_free;

	path = ft_getenv("PATH");
	if (path[0] == '\0')
	{
		free(path);
		return (NULL);
	}
	paths = ft_split(path, ':');
	free(path);
	i = 0;
	while (paths[i])
	{
		to_free = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(to_free);
		i++;
	}
	return (paths);
}

char	*find_executable(t_command *cmd)
{
	char				*executable;
	char				**paths;
	int unsigned		i;

	if (!cmd->name)
		return (NULL);
	if (access(cmd->name, X_OK) == 0)
		return (ft_strdup(cmd->name));
	paths = get_paths();
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		executable = ft_strjoin(paths[i], cmd->name);
		if (access(executable, X_OK) == 0)
		{
			ft_delete_matrice(paths);
			return (executable);
		}
		free(executable);
		i++;
	}
	ft_delete_matrice(paths);
	return (NULL);
}

char	**list_to_array(t_env *vars)
{
	char			**array;
	t_env			*tmp;
	int unsigned	len;
	int unsigned	i;

	len = 0;
	tmp = vars;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	array = ft_calloc(len + 1, sizeof(char *));
	tmp = vars;
	i = 0;
	while (tmp)
	{
		array[i] = ft_strjoin_three(tmp->key, "=", tmp->value, FALSE);
		i++;
		tmp = tmp->next;
	}
	return (array);
}
