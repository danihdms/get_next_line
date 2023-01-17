/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaydamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:01:46 by dhaydamo          #+#    #+#             */
/*   Updated: 2023/01/17 15:05:37 by dhaydamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	read_line(t_buffer *buffer, int fd)
{
	ssize_t	value;

	value = read(fd, buffer->buff, BUFFER_SIZE);
	if (value < 0)
		return (value);
	buffer->pos = 0;
	buffer->len = value;
	return (value);
}

size_t	buff_len(t_buffer *buffer)
{
	size_t	acc;
	size_t	filled;
	char	*content;

	acc = 0;
	filled = buffer->pos;
	content = buffer->buff;
	while (acc + filled < buffer->len)
	{
		acc++;
		if (content[filled + acc - 1] == '\n')
			break ;
	}
	return (acc);
}

char	*cat_buff(t_buffer *buffer, t_line *line)
{
	char	*new_line;
	size_t	line_len;

	line_len = buff_len(buffer);
	new_line = malloc(sizeof(char) * (line->len + line_len + 1));
	if (!new_line)
	{
		free(line->content);
		return (NULL);
	}
	if (line->len > 0)
		str_cpy(new_line, line->content);
	else
		new_line[0] = 0;
	str_n_cat(new_line, &buffer->buff[buffer->pos], line_len);
	free(line->content);
	line->len += line_len;
	buffer->pos += line_len;
	return (new_line);
}

char	*get_next_line(int fd)
{
	t_line			line;
	t_buffer		*buffer;
	static t_buffer	*first_buffer = NULL;

	line.len = 0;
	line.content = NULL;
	buffer = get_buffer(&first_buffer, fd);
	if (!buffer)
		return (NULL);
	while (1)
	{
		if (buffer->pos == buffer->len)
		{
			if (read_line(buffer, fd) < 0)
				return (delete_buffer(&first_buffer, fd), free(line.content),
					NULL);
			if (!buffer->len)
				return (delete_buffer(&first_buffer, fd), line.content);
		}
		line.content = cat_buff(buffer, &line);
		if (!(line.content))
			return (delete_buffer(&first_buffer, fd), NULL);
		if (buffer->buff[buffer->pos - 1] == '\n')
			return (line.content);
	}
}
