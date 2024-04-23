/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:37:29 by matesant          #+#    #+#             */
/*   Updated: 2024/04/23 15:46:24 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_in_order(char **key)
{
	int		i;
	t_env	*env;

	i = 0;
	env = ft_get_shell()->env_list;
	while (key[i])
	{
		while (env)
		{
			if (!ft_strcmp(key[i], env->key))
			{
				if (env->value && ft_strlen(env->value) > 0)
					ft_printf_fd(STDOUT_FILENO, "declare -x %s=\"%s\"\n",
						env->key, env->value);
				else if (!env->value && env->equal == 0)
					ft_printf_fd(STDOUT_FILENO, "declare -x %s\n", env->key);
				else
					ft_printf_fd(STDOUT_FILENO, "declare -x %s=\"\"\n", env->key);
				break ;
			}
			env = env->next;
		}
		env = ft_get_shell()->env_list;
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
