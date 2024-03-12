/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:50:05 by almarcos          #+#    #+#             */
/*   Updated: 2024/03/12 07:50:06 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H

# define DEFINE TYPES_H

typedef struct s_command
{
	char				*name;
	char				**argv;
	int					tube[2];
	bool				output_to_pipe;
	struct s_command	*prev;
	struct s_command	*next;
}					t_command;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_minishell
{
	char			*user_input;
	t_token			*tokens;
	t_command		*commands;
}					t_minishell;

#endif
