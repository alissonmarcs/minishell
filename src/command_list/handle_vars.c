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

static void	update_argv(t_command *last, char **split);
static void	export(t_command *last, t_token *token);
static void	others_cases(t_token *tokens, t_command *last);

void	handle_vars(t_token **tokens, t_command *last)
{
	if ((*tokens)->str && (*tokens)->str[0])
	{
		if (ft_strcmp(last->name, "export") == 0)
			export(last, *tokens);
		else
			others_cases(*tokens, last);
	}
	*tokens = (*tokens)->next;
}

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

static void	export(t_command *last, t_token *token)
{
	char	**new_argv;
	int		len;

	if (!last->argv)
	{
		last->argv = ft_calloc(3, sizeof(char *));
		last->argv[0] = ft_strdup(last->name);
		last->argv[1] = ft_strdup(token->str);
	}
	else
	{
		len = ft_matrice_len(last->argv);
		new_argv = ft_calloc(len + 2, sizeof(char *));
		ft_memmove(new_argv, last->argv, len * sizeof(char *));
		new_argv[len] = ft_strdup(token->str);
		free(last->argv);
		last->argv = new_argv;
	}
}

static void	others_cases(t_token *tokens, t_command *last)
{
	char	**split;

	split = ft_split(tokens->str, ' ');
	if (!last->name && !last->argv)
	{
		last->name = ft_strdup(split[0]);
		last->argv = split;
	}
	else if (last->name && last->argv)
		update_argv(last, split);
	else if (last->name && !last->argv)
	{
		last->argv = ft_calloc(ft_matrice_len(split) + 2,
				sizeof(char *));
		last->argv[0] = ft_strdup(last->name);
		ft_memmove(last->argv + 1, split, ft_matrice_len(split)
			* sizeof(char *));
		free(split);
	}
}
