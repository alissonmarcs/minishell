#include "minishell.h"

void	check_here_doc(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == HERE_DOC)
			execute_here_doc(tokens);
		tokens = tokens->next;
	}
}

void	execute_here_doc(t_token *tokens)
{
	
}
