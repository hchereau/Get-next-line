/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:18:40 by hchereau          #+#    #+#             */
/*   Updated: 2023/01/12 16:39:45 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define FD_TOTAL 1024

size_t	get_index(char *str, const char c, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size && str[index] != c)
		++index;
	return (index);
}

void	add_rest(char **line, char *dest, char *src, size_t index)
{
	add_str(line, src, index + 1);
	ft_strlcpy(dest, src + index + 1, BUFFER_SIZE - index + 1);
}

void	fill_line(char **line, char *rest, size_t index, int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	size_t		bytes_count;

	add_str(line, rest, ft_strlen(rest));
	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes_count = read(fd, buffer, BUFFER_SIZE);
	index = get_index(buffer, '\n', BUFFER_SIZE);
	while (index == BUFFER_SIZE && bytes_count > 0)
	{
		add_str(line, buffer, bytes_count);
		ft_bzero(buffer, BUFFER_SIZE);
		bytes_count = read(fd, buffer, BUFFER_SIZE);
		index = get_index(buffer, '\n', BUFFER_SIZE);
	}
	if (bytes_count > 0)
		add_rest(line, rest, buffer, index);
}

char	*get_next_line(int fd)
{
	static char	rest[FD_TOTAL][BUFFER_SIZE + 1] = {{0}};
	char		*str_final;
	ssize_t		index;

	str_final = NULL;
	if (fd < FD_TOTAL && fd >= 0)
	{
		index = get_index(rest[fd], '\n', BUFFER_SIZE);
		if (index < BUFFER_SIZE)
			add_rest(&str_final, rest[fd], rest[fd], index);
		else
			fill_line(&str_final, rest[fd], index, fd);
	}
	return (str_final);
}
