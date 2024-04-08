/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:49:57 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/02 12:06:54 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H

# define DEFINES_H

# define YELLOW "\001\x1B[1;33m\002"

# define RESET "\033[0m"

# define PROMPT YELLOW"CarlitoShell$ "RESET

# define RED "\001\e[0m\002\e[31m"

# define PROMPT2 "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"

# define AND_ERROR "syntax error near unexpected token `&&'"

# define HERE_DOC_FILE "/tmp/minishell_heredoc_"

typedef enum e_bool
{
	FALSE,
	TRUE
}		t_bool;

enum	e_token
{
	SPACES = 1,
	VAR,
	WORD,
	PIPE,
	INPUT,
	TRUNC,
	APPEND,
	HERE_DOC,
	END,
};

#endif
