/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:57:36 by matesant          #+#    #+#             */
/*   Updated: 2024/02/20 12:25:44 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*handle_read_error(ssize_t read_bytes, char *line_buffer,
		char *new_line)
{
	if (read_bytes < 0 || (read_bytes == 0 && !*new_line))
	{
		free(line_buffer);
		free(new_line);
		return (NULL);
	}
	return (new_line);
}

static char	*ft_get_new_line(int fd, char *new_line)
{
	char	*line_buffer;
	ssize_t	read_bytes;

	line_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line_buffer)
		return (NULL);
	if (!new_line)
		new_line = g_ft_strdup("");
	read_bytes = 1;
	while ((!g_ft_strchr(new_line, '\n')) && read_bytes)
	{
		read_bytes = read(fd, line_buffer, BUFFER_SIZE);
		new_line = handle_read_error(read_bytes, line_buffer, new_line);
		if (!new_line)
			return (NULL);
		line_buffer[read_bytes] = '\0';
		new_line = g_ft_strjoin(new_line, line_buffer);
	}
	free(line_buffer);
	return (new_line);
}

static char	*ft_make_new_line(char *content_line)
{
	char	*line_position;
	char	*new_line;
	size_t	line_size;

	line_position = g_ft_strchr(content_line, '\n');
	if (line_position == NULL)
		return (g_ft_strdup(content_line));
	else
		line_size = ((line_position - content_line) + 2);
	new_line = malloc(line_size);
	g_ft_strlcpy(new_line, content_line, line_size);
	return (new_line);
}

static char	*ft_update_after_new_line(char *line_to_update)
{
	char	*line_position;
	char	*rest_of_the_line;

	line_position = g_ft_strchr(line_to_update, '\n');
	if (line_position == NULL)
	{
		free(line_to_update);
		return (NULL);
	}
	rest_of_the_line = g_ft_strdup(line_position + 1);
	free(line_to_update);
	return (rest_of_the_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*next_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		free(next_line);
		next_line = NULL;
		return (NULL);
	}
	next_line = ft_get_new_line(fd, next_line);
	if (next_line == NULL)
		return (NULL);
	line = ft_make_new_line(next_line);
	next_line = ft_update_after_new_line(next_line);
	return (line);
}
