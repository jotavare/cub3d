/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:34:21 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 00:34:22 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

#define BUFFER_SIZE 8192

typedef struct s_buffer	t_buffer;
struct s_buffer
{
	char	str[BUFFER_SIZE];
	size_t	i;
	int		res;
	int		started;
};

char	*ft_strnjoin(char *s1, char const *s2, size_t n)
{
	char	*new;
	int		i;
	char	*s1_start;

	if (!s1)
		return (ft_strndup(s2, n));
	new = malloc(sizeof(char) * (ft_strlen(s1) + n + 1));
	if (!new)
		return (0);
	i = 0;
	s1_start = s1;
	while (*s1)
	{
		new[i++] = *s1;
		s1++;
	}
	while (n)
	{
		new[i++] = *s2;
		s2++;
		n--;
	}
	new[i] = 0;
	free(s1_start);
	return (new);
}

size_t	ft_get_end_of_buffer_index(t_buffer buffer)
{
	size_t			end_of_buffer;

	end_of_buffer = BUFFER_SIZE;
	if (buffer.res != BUFFER_SIZE)
		end_of_buffer = buffer.res;
	return (end_of_buffer);
}

int	ft_set_join(char **join, t_buffer *buffer)
{
	size_t			end_of_buffer;
	size_t			i;
	size_t			up_to;
	char			*newline_in_str;

	end_of_buffer = ft_get_end_of_buffer_index(*buffer);
	if (buffer->i >= end_of_buffer)
		return (ft_bzero(buffer, sizeof(t_buffer)), 0);
	i = buffer->i;
	newline_in_str = ft_strnchr(buffer->str + i, '\n', end_of_buffer - 1);
	if (newline_in_str)
		up_to = newline_in_str - (buffer->str + i) + 1;
	else
		up_to = end_of_buffer - i;
	buffer->i += up_to;
	*join = ft_strnjoin(*join, buffer->str + i, up_to);
	if (!*join)
	{
		*join = 0;
		ft_bzero(buffer, sizeof(t_buffer));
		return (0);
	}
	return (!newline_in_str);
}

void	ft_buffer_read(int fd, t_buffer *buffer)
{
	buffer->res = read(fd, buffer->str, BUFFER_SIZE);
	buffer->started = 1;
	buffer->i = 0;
}

char	*get_next_line(int fd)
{
	static t_buffer	buffers[FOPEN_MAX];
	char			*join;

	if (fd < 0 || (buffers[fd].res <= 0 && buffers[fd].started))
		return (0);
	join = 0;
	while (1)
	{
		if (buffers[fd].i >= BUFFER_SIZE || !buffers[fd].started)
		{
			ft_buffer_read(fd, buffers + fd);
			if (buffers[fd].res == 0)
				return (ft_bzero(buffers + fd, sizeof(t_buffer)), join);
			if (buffers[fd].res == -1)
			{
				ft_bzero(buffers + fd, sizeof(t_buffer));
				if (join)
					free(join);
				return (0);
			}
		}
		if (!ft_set_join(&join, buffers + fd))
			return (join);
	}
	return (join);
}
