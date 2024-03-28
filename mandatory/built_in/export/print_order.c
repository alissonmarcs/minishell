/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:37:29 by matesant          #+#    #+#             */
/*   Updated: 2024/03/28 17:55:39 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_in_order(char **env)
{
	int		i;
	char	*key;
	t_env	*envl;

	i = 0;
	envl = ft_get_shell()->env_list;
	while (env[i])
	{
		while (envl)
		{
			key = envl->key;
			if (!ft_strcmp(env[i], key))
			{
				if (envl->value)
					ft_printf_fd(STDOUT_FILENO, "declare -x %s=%s\n", envl->key,
						envl->value);
				else if (!envl->value)
					ft_printf_fd(STDOUT_FILENO, "declare -x %s=\n", envl->key);
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
