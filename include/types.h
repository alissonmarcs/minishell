/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:50:05 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/04 13:57:45 by matesant         ###   ########.fr       */
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
	char				*path;
	char				**argv;
	int					pipe[2];
	t_bool				output_to_pipe;
	pid_t				pid;
	t_io				*io;
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

typedef struct s_token
{
	char				*str;
	enum e_token		type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
	int					equal;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_v
{
	char				*key;
	char				*value;
}						t_v;

typedef struct s_gc
{
	void				**content;
	struct s_gc			*next;
}						t_gc;

typedef struct s_minishell
{
	char				*user_input;
	char				**env;
	t_token				*tokens;
	t_env				*env_list;
	t_command			*commands;
	int					exit_status;
	int					standard_fds[2];
	char				teemo;
	t_gc				*gc;
	pid_t				last_child;
}						t_minishell;

#endif
