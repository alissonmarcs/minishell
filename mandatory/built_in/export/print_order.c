/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:37:29 by matesant          #+#    #+#             */
/*   Updated: 2024/04/02 17:10:00 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_in_order(char **env)
{
	int		i;
	t_env	*envl;

	i = 0;
	envl = ft_get_shell()->env_list;
	while (env[i])
	{
		while (envl)
		{
			if (!ft_strcmp(env[i], envl->key))
			{
				if (envl->value && ft_strlen(envl->value) > 0)
					ft_printf_fd(STDOUT_FILENO, "declare -x %s=\"%s\"\n",
						envl->key, envl->value);
				else if (envl->value && envl->equal == 0)
					ft_printf_fd(STDOUT_FILENO, "declare -x %s\n", envl->key);
				else
					ft_printf_fd(STDOUT_FILENO, "declare -x %s=\"\"\n",
						envl->key);
				break ;
			}
			envl = envl->next;
		}
		envl = ft_get_shell()->env_list;
		i++;
	}
}

int	ft_envsize(t_env *env)
{
	size_t	items;

	if (env == NULL)
		return (0);
	items = 1;
	while (env->next != NULL)
	{
		items++;
		env = env->next;
	}
	return (items);
}

t_bool	ft_already_exists(char *key)
{
	t_env	*env;

	env = ft_get_shell()->env_list;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}

void	ft_change_value(char *key, char *value, int equal)
{
	t_env	*env;

	env = ft_get_shell()->env_list;
	while (env)
	{
		if (env->key && !ft_strcmp(env->key, key) && equal == 1)
		{
			free(env->value);
			env->value = ft_strdup(value);
			env->equal = equal;
			break ;
		}
		env = env->next;
	}
}

void	ft_reset_v(t_v **v)
{
	ft_free_ptr((void **)&(*v)->key);
	ft_free_ptr((void **)&(*v));
	*v = 0;
}
