/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:49:57 by almarcos          #+#    #+#             */
/*   Updated: 2024/03/19 18:42:50 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H

# define DEFINES_H

# define PROMPT "\001\e[0m\002\e[33mCarlitoShell$ \001\e[0m\002"

# define RED "\001\e[0m\002\e[31m"

# define RESET "\001\e[0m\002"

# define AND_ERROR "syntax error near unexpected token `&&'"

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
