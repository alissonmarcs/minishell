/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:54:16 by almarcos          #+#    #+#             */
/*   Updated: 2024/03/15 09:54:17 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_minishell *shell)
{
	int		i;
	char	**env;

	i = 0;
	while (__environ[i])
		i++;
	env = ft_calloc(i + 1, sizeof (char *));
	i = 0;
	while (__environ[i])
	{
		env[i] = ft_strdup(__environ[i]);
		i++;
	}
	shell->env = env;
}
