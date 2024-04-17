/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:34:04 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/16 14:34:05 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_args(t_token **tokens, t_command *last);
static void	create_argv(t_token **tokens, t_command *last);
static void	add_to_argv(t_token **tokens, t_command *last);
static int	get_len_args(t_token *token);

void	handle_words(t_token **token, t_command *last)
{
	t_token	*tmp;

	tmp = *token;
	if (!last->name)
	{
		last->name = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	else
		get_args(&tmp, last);
	*token = tmp;
}

static void	get_args(t_token **tokens, t_command *last)
{
	if (!last->argv)
		create_argv(tokens, last);
	else
		add_to_argv(tokens, last);
}

static void	create_argv(t_token **tokens, t_command *last)
{
	int		count_args;
	t_token	*tmp;
	int		i;

	tmp = *tokens;
	count_args = get_len_args(*tokens);
	last->argv = ft_calloc(count_args + 2, sizeof(char *));
	last->argv[0] = ft_strdup(last->name);
	i = 1;
	while (tmp->type == WORD)
	{
		last->argv[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	*tokens = tmp;
}

static void	add_to_argv(t_token **tokens, t_command *last)
{
	char	**new_argv;
	int		argv_len;
	int		count_new_args;
	t_token	*tmp;

	argv_len = ft_matrice_len(last->argv);
	count_new_args = get_len_args(*tokens);
	new_argv = ft_calloc(argv_len + count_new_args + 1, sizeof(char *));
	ft_memmove(new_argv, last->argv, argv_len * sizeof(char *));
	tmp = *tokens;
	while (tmp->type == WORD)
	{
		new_argv[argv_len] = ft_strdup(tmp->str);
		argv_len++;
		tmp = tmp->next;
	}
	free(last->argv);
	last->argv = new_argv;
	*tokens = tmp;
}

static int	get_len_args(t_token *token)
{
	int	i;

	i = 0;
	while (token->type == WORD)
	{
		i++;
		token = token->next;
	}
	return (i);
}
