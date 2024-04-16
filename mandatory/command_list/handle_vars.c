/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:34:00 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/16 14:34:01 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_argv(t_command *last, char **split)
{
	char	**new_argv;
	int		split_len;
	int		old_len;

	old_len = ft_matrice_len(last->argv);
	split_len = ft_matrice_len(split);
	new_argv = ft_calloc(old_len + split_len + 1, sizeof(char *));
	ft_memmove(new_argv, last->argv, old_len * sizeof(char *));
	ft_memmove(new_argv + old_len, split, split_len * sizeof(char *));
	free(split);
	free(last->argv);
	last->argv = new_argv;
}

void	handle_vars(t_token **tokens, t_command *last)
{
	char	**split;

	if ((*tokens)->str && (*tokens)->str[0])
	{
		split = ft_split((*tokens)->str, ' ');
		if (!last->name && !last->argv)
		{
			last->name = ft_strdup(split[0]);
			last->argv = split;
		}
		else if (last->name && last->argv)
			update_argv(last, split);
		else if (last->name && !last->argv)
		{
			last->argv = ft_calloc(ft_matrice_len(split) + 2, sizeof(char *));
			last->argv[0] = ft_strdup(last->name);
			ft_memmove(last->argv + 1, split, ft_matrice_len(split)
				* sizeof(char *));
			free(split);
		}
	}
	*tokens = (*tokens)->next;
}
