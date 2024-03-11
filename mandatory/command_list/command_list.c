#include "minishell.h"

t_command	*new_command(char *name, bool pipe)
{
	t_command *command;

	command = ft_calloc(1, sizeof (t_command));
	if (!command)
		return (NULL);
	command->name = name;
	command->output_to_pipe = pipe;
	return (command);
}

void	append_command(t_command **cmd_list, t_command *new)
{
	t_command *tmp;

	if (!*cmd_list)
		*cmd_list = new;
	else
	{
		tmp = *cmd_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

void	print_cmd_list(t_command *list)
{
	printf("\n\n\n\t\t------ COMMAND LIST ------\n\n\n");
	while (list)
	{
		printf("\t---- Name: %s\n", list->name);
		printf("\t---- Output to pipe: %d\n", list->output_to_pipe);
		printf("\t---- Prev: %p\n", list->prev);
		if (list->prev)
			printf("\t\t---- Name: %s\n", list->prev->name);
		printf("\t---- Next: %p\n", list->next);
		if (list->next)
			printf("\t\t---- Name: %s\n", list->next->name);
		printf("\n\n");
		list = list->next;
	}
}

void	free_cmd_list(t_command **cmd_list)
{
	t_command *tmp;
	t_command *next;

	tmp = *cmd_list;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->name);
		free(tmp);
		tmp = next;
	}
	*cmd_list = NULL;
}
