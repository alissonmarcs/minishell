/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:50:05 by almarcos          #+#    #+#             */
/*   Updated: 2024/03/19 12:50:25 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H

# define DEFINE TYPES_H

typedef struct s_io
{
	char				*infile;
	char				*outfile;
	int					infile_fd;
	int					outfile_fd;
}						t_io;

typedef struct s_command
{
	char				*name;
	char				**argv;
	int					tube[2];
	t_bool				output_to_pipe;
	t_io				*io;
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

typedef struct s_token
{
	char				*str;
	int					type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_minishell
{
	char				*user_input;
	char				**env;
	t_token				*tokens;
	t_env				*env_list;
	t_command			*commands;
}						t_minishell;

typedef struct s_exp
{
	char				*var;
	char				*value;
	char				*init;
	char				*end;
	char				*line;
}						t_exp;

#endif
