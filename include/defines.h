/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:49:57 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/09 19:35:18 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H

# define DEFINES_H

# define YELLOW "\001\033[33m\002"

# define RESET "\001\033[0m\002"

# define RED "\001\e[0m\002\e[31m"

# define AND_ERROR "syntax error near unexpected token `&&'"

# define HERE_DOC_FILE "/tmp/minishell_heredoc_"

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
