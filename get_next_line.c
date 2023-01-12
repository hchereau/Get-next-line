/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:18:40 by hchereau          #+#    #+#             */
/*   Updated: 2023/01/12 02:51:13 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_index(char *str, const char c, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (str[i] == c)
		{
			return (i);
		}
		++i;
	}
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
	static char	rest[BUFFER_SIZE + 1] = {0};
	char		*str_final;
	ssize_t		index;

	str_final = NULL;
	if (fd != -1)
	{
		index = get_index(rest, '\n', BUFFER_SIZE);
		if (index < BUFFER_SIZE)
			add_rest(&str_final, rest, rest, index);
		else
			fill_line(&str_final, rest, index, fd);
	}
	return (str_final);
}

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

/*
process 2:

verifier si \n dans rest(get_index(rest, '\n', BUFFER_SIZE))
	-> malloc str_final 
	-> ajouter le rest jusqu'a l'index dans str_final
	-> rest = ce qu'il y a apres le \n jusqu'a la fin du rest (strlcpy)
	return str_final
si pas de \n dans rest
	-> ajouter rest au debut de str_final 
	-> bytes_count = read(fd, buffer, BUFFER_SIZE)
	-> tant que index == -1
		-> str_final = add_str(str_final, buffer, BUFFER_SIZE)
		-> bytes_count = read(fd, buffer, BUFFER_SIZE)
		-> index = get_index(buffer, '\n', BUFFER_SIZE)
	-> str_final = add_str(str_final, buffer, index + 1)
	-> strlcpy(rest, buffer + index, BUFFER_SIZE - index)
-> return(str_final)






ft_strjoin()
ft_strlcpy()
ft_strlen()
get_index()
ft_bzero()

get_index
goal : recuperer l'indice du \n dans BUFFER, -1 si il n'y en a pas
inputs : BUFFER, \n
process :
-> parcourir la chaine BUFFER
-> si \n 
return (index)
-> return -1
 */
