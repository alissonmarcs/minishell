/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:42:50 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/16 14:42:51 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_herdoc_file	*new_file(char *file_name)
{
	t_herdoc_file	*node;

	node = ft_calloc(1, sizeof(t_herdoc_file));
	node->file = file_name;
	return (node);
}

t_herdoc_file	*get_last_file(t_herdoc_file *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	append_file(t_herdoc_file **head, t_herdoc_file *new)
{
	if (!*head)
		*head = new;
	else
		get_last_file(*head)->next = new;
}

void	free_here_docs(t_heredoc **hd)
{
	int unsigned	i;
	t_herdoc_file	*next;
	t_herdoc_file	*current;

	if (!*hd)
		return ;
	i = 0;
	while (i < (*hd)->size)
	{
		current = (*hd)->array[i];
		while (current)
		{
			next = current->next;
			free(current->file);
			free(current);
			current = next;
		}
		i++;
	}
	free((*hd)->array);
	free(*hd);
	*hd = NULL;
}
