/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:14:55 by hchereau          #+#    #+#             */
/*   Updated: 2023/02/15 12:14:59 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_index(char *str, const char c, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && str[i] != '\0' && str[i] != c)
		++i;
	return (i);
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

	add_rest(line, rest, rest, ft_strlen(rest));
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
	if (bytes_count == 0)
	{
		add_rest(line, rest, buffer, index);
		ft_bzero(rest, BUFFER_SIZE + 1);
	}
}

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE + 1] = {0};
	char		*str_final;
	ssize_t		index;

	str_final = NULL;
	if (fd != -1)
	{
		index = get_index(rest, '\n', BUFFER_SIZE);
		if (index < BUFFER_SIZE && rest[index] == '\n')
			add_rest(&str_final, rest, rest, index);
		else
			fill_line(&str_final, rest, index, fd);
	}
	return (str_final);
}

/*
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc <= 1)
		return (EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("[%s]", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
*/
