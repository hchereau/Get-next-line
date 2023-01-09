/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:18:40 by hchereau          #+#    #+#             */
/*   Updated: 2023/01/09 17:49:30 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_index()

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	char		*str_final;
	char		*buffer;
	size_t		bytes_count;
	size_t		is_index;
	
	str_final = NULL;
	str_final = ft_strnjoin(str_final, rest, ft_strlen(rest));
	bytes_count = read(fd, buffer, BUFFER_SIZE);
	is_index = get_index(buffer,'\n');
	while (is_index == -1)
	{
		add_str(&str_final, buffer, BUFFER_SIZE);
	}
	add_str()
	return 
}

int main(int argc, char **argcv)
{
	int	fd;
	int i;

	fd = open("readthis.txt", O_RDONLY);
	i = 0;
	while (i <= argcv[1])
	{
		get_next_line(fd);
		++i;
	}
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
