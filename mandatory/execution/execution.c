#include "minishell.h"

void	restore_standard_fds(t_minishell *shell)
{
	dup2(shell->standard_fds[0], STDIN_FILENO);
	dup2(shell->standard_fds[1], STDOUT_FILENO);
}
