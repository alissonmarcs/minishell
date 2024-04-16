/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:44:10 by matesant          #+#    #+#             */
/*   Updated: 2024/04/16 17:13:31 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env_token(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	ft_change_lane(t_env **head, t_env *to_delete)
{
	if (to_delete->prev)
		to_delete->prev->next = to_delete->next;
	if (to_delete->next)
		to_delete->next->prev = to_delete->prev;
	if (!to_delete->prev)
		*head = to_delete->next;
	ft_free_env_token(to_delete);
}

void	ft_unset_env(char *argv)
{
	t_env	*env;

	env = ft_get_shell()->env_list;
	while (env)
	{
		if (!ft_strcmp(env->key, argv))
		{
			ft_change_lane(&ft_get_shell()->env_list, env);
			break ;
		}
		env = env->next;
	}
}

void	ft_unset(char **argv)
{
	int	i;

	i = 1;
	ft_get_shell()->exit_status = 0;
	while (argv[i])
	{
		if (ft_valid_key(argv[i]) || ft_isdigit(argv[i][0]))
		{
			ft_printf_fd(2, "minishell: unset: `%s': not a valid identifier\n",
				argv[i]);
			ft_get_shell()->exit_status = 1;
			i++;
			continue ;
		}
		ft_unset_env(argv[i]);
		i++;
	}
}
