/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:54:16 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/02 16:30:29 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_get_env_list(void)
{
	char		*key;
	char		*value;
	char		*ptr;
	char		**env;

	env = ft_get_shell()->env;
	while (*env)
	{
		ptr = ft_strchr(*env, '=');
		key = ft_substr(*env, 0, ptr - *env);
		value = ft_strdup(ptr + 1);
		ft_lstend_var(&ft_get_shell()->env_list, key, value, 0);
		free(key);
		free(value);
		env++;
	}
	ft_get_shell()->env = NULL;	
}

void	ft_clone_env(t_minishell *shell)
{
	shell->env = __environ;
	ft_get_env_list();
}

char	*ft_getenv(char *env)
{
	t_minishell	*shell;
	t_env		*curr;

	shell = ft_get_shell();
	curr = shell->env_list;
	if (!env)
		return (NULL);
	while (curr)
	{
		if (!ft_strcmp(curr->key, env))
			return (ft_strdup(curr->value));
		if (!ft_strcmp(env, "?"))
			return (ft_itoa(shell->exit_status));
		if (!ft_strcmp(env, "$"))
			return (ft_strdup(&shell->teemo));
		curr = curr->next;
	}
	if (!curr)
		return (ft_strdup(""));
	return (NULL);
}

void	get_standard_fds(t_minishell *shell)
{
	shell->standard_fds[0] = dup(STDIN_FILENO);
	shell->standard_fds[1] = dup(STDOUT_FILENO);
}
