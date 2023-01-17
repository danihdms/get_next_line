#include "get_next_line.h"

t_buffer	*add_buffer(t_buffer **first_buffer, int fd)
{
	t_buffer	*buffer;
	t_buffer	*new;

	buffer = *first_buffer;
	new = malloc(sizeof(t_buffer));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->pos = 0;
	new->len = 0;
	new->next = NULL;
	if (*first_buffer == NULL)
		*first_buffer = new;
	else
	{
		while (buffer->next)
			buffer = buffer->next;
		buffer->next = new;
	}
	return (new);
}

t_buffer	*get_buffer(t_buffer **first_buffer, int fd)
{
	t_buffer	*buffer;

	buffer = *first_buffer;
	while (buffer && buffer->fd != fd)
		buffer = buffer->next;
	if (!buffer)
		buffer = add_buffer(first_buffer, fd);
	return (buffer);
}

void	delete_buffer(t_buffer **first_buffer, int fd)
{
	t_buffer	*current;
	t_buffer	*next;

	current = *first_buffer;
	next = current->next;
	if ((*first_buffer)->fd == fd)
	{
		free(*first_buffer);
		*first_buffer = next;
		return ;
	}
	while (next)
	{
		if (next->fd == fd)
		{
			current->next = next->next;
			free(next);
			return ;
		}
		current = next;
		next = next->next;
	}
}

char	*str_cpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*str_n_cat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (j < n)
	{
		dest[i + j] = src [j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
