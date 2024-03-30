/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:44:10 by matesant          #+#    #+#             */
/*   Updated: 2024/03/29 22:08:31 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_env_token(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void ft_change_lane(t_env **env, t_env *prev, t_env *next)
{
	if (prev)
		(*env)->prev->next = next;
	if (next)
		(*env)->next->prev = prev;
	ft_free_env_token(*env);
}

void ft_unset_env(char *argv)
{
	t_env *env;
	t_env *prev;
	t_env *next;

	env = ft_get_shell()->env_list;
	prev = NULL;
	while (env)
	{
		if (!ft_strcmp(env->key, argv))
		{
			prev = env->prev;
			next = env->next;
			ft_change_lane(&env, prev, next);
			env = ft_get_shell()->env_list;
		}
		env = env->next;
	}    
}

void ft_unset(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		ft_unset_env(argv[i]);
		i++;
	}
}
