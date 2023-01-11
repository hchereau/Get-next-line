/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:18:40 by hchereau          #+#    #+#             */
/*   Updated: 2023/01/11 13:59:11 by hchereau         ###   ########.fr       */
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
			return(i);
		++i;
	}
	return(-1);
}

int	is_valid_line(char *rest)
{
	return (get_index(rest, '\n', ft_strlen(rest)) != -1);
}

void	add_rest(char **final_str, char *rest)
{
	ssize_t	size;

	size = get_index(rest, '\n', ft_strlen(rest));
	if (size == -1)
		size = ft_strlen(rest);
	add_str(final_str, rest, size);

}

void	refresh_rest(char *rest, char *buffer)
{
	ssize_t	size;

	size = get_index(rest, '\n', ft_strlen(rest));
	if (size == -1)
		size = ft_strlen(rest);
	ft_strlcpy(rest, buffer + size + 1, BUFFER_SIZE - size);
}

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE] = {0};
	char		buffer[BUFFER_SIZE + 1];
	char		*str_final;
	size_t		bytes_count;
	ssize_t		index;

	str_final = NULL;
	if (is_valid_line(rest) == true)
	{
		add_rest(&str_final, rest);
		refresh_rest(rest, rest + get_index(rest, '\n', BUFFER_SIZE));
	}
	else
	{
		add_rest(&str_final, rest);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		bytes_count = read(fd, buffer, BUFFER_SIZE);
		index = get_index(buffer, '\n', bytes_count);
		while (index == -1 && bytes_count > 0)
		{
			add_str(&str_final, buffer, bytes_count);
			bytes_count = read(fd, buffer, BUFFER_SIZE);
			index = get_index(buffer, '\n', bytes_count);
		}
		add_str(&str_final, buffer, index + 1);
		refresh_rest(rest, buffer);
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
		printf("[%s]", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

/*
process:

ajouter le static BUFFER de la ligne precedent au debut de la str final
read sur BUFFERR size
parcourir BUFFER jusqu'a tomber sur \n
si pas de \n:
join la str final et le BUFFER sur une nouvelle ligne
free la ligne precedente
si \n:
ajouter \n a str final
garder en static suite BUFFER








process 2:

verifier si pas de \n dans rest(get_index(rest, '\n', BUFFER_SIZE))
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
	-> strlcpy(rest, buffer + index, )
decoupage fonction:











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
