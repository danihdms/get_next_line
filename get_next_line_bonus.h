/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaydamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:02:00 by dhaydamo          #+#    #+#             */
/*   Updated: 2023/01/17 15:14:11 by dhaydamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	64
# endif

typedef struct s_buffer
{
	int				fd;
	char			buff[BUFFER_SIZE];
	size_t			len;
	size_t			pos;
	struct s_buffer	*next;
}		t_buffer;

typedef struct s_line
{
	size_t	len;
	char	*content;
}		t_line;

char		*get_next_line(int fd);

char		*cat_buff(t_buffer *buffer, t_line *line);

size_t		buff_len(t_buffer *buffer);

char		*str_cpy(char *dest, const char *src);

char		*str_n_cat(char *dest, const char *src, size_t n);

ssize_t		read_line(t_buffer *buffer, int fd);

t_buffer	*get_buffer(t_buffer **first_buffer, int fd);

t_buffer	*add_buffer(t_buffer **first_buffer, int fd);

void		delete_buffer(t_buffer **first_buffer, int fd);

#endif
