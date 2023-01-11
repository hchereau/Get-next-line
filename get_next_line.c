/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:18:40 by hchereau          #+#    #+#             */
/*   Updated: 2023/01/12 00:40:53 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	get_index(char *str, const char c, size_t size)
{
	size_t	i;

	i = 0;
	while(i < size)
	{
		if (str[i] == c)
		{
			return(i);
		}
		++i;
	}
	return(-1);
}

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE] = {0};
	char		buffer[BUFFER_SIZE + 1];
	char		*str_final;
	size_t		bytes_count;
	ssize_t		index;

	str_final = NULL;
	index = get_index(rest, '\n', BUFFER_SIZE);
	if (index != -1)
	{
		ft_strlcpy(rest, rest + index + 1, BUFFER_SIZE - index + 1);
	}
	else
	{
		add_str(&str_final, rest, ft_strlen(rest));
		bytes_count = read(fd, buffer, BUFFER_SIZE);
		while(index == -1 && bytes_count > 0)
		{
			add_str(&str_final, buffer, BUFFER_SIZE);
			bytes_count = read(fd, buffer, BUFFER_SIZE);
			index = get_index(buffer, '\n', BUFFER_SIZE);
		}
		if (index != -1)
		{
			add_str(&str_final, buffer, index);
			ft_strlcpy(rest, buffer + index + 1, BUFFER_SIZE - index + 1);
		}
		else
			ft_bzero(rest, BUFFER_SIZE);
	}	
	return (str_final);
}

int main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc < 1)
		return (0);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
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
