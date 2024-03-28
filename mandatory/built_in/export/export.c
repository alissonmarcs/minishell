/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:05:22 by matesant          #+#    #+#             */
/*   Updated: 2024/03/28 19:06:46 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arrange(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ft_clonenvlst(void)
{
	char	**env;
	t_env	*cur;
	int		i;

	i = 0;
	cur = ft_get_shell()->env_list;
	env = ft_calloc(sizeof(char *), (ft_envsize(ft_get_shell()->env_list) + 1));
	while (cur)
	{
		env[i] = ft_strdup(cur->key);
		cur = cur->next;
		i++;
	}
	ft_arrange(env);
	ft_print_in_order(env);
	ft_delete_matrice(env);
}

t_bool	ft_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]))
		return (TRUE);
	while (key[i])
	{
		if (!ft_isalnum(key[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	ft_add_var(char **argv)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	value = NULL;
	key = NULL;
	while (argv[i])
	{
		key = ft_substr(argv[i], 0, ft_strchr(argv[i], '=') - argv[i]);
		value = ft_strchr(argv[i], '=');
		if (value)
			value++;
		if (!ft_valid_key(key))
			ft_lstend_var(&ft_get_shell()->env_list, key, value);
		else
		{
			ft_invalid_key(key, value);
			free(key);
			return ;
		}
		free(key);
		i++;
	}
}

void	ft_export(char **argv)
{
	if (ft_matrice_len(argv) == 1)
	{
		ft_clonenvlst();
		return ;
	}
	else
		ft_add_var(argv);
}
