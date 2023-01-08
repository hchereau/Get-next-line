/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:18:40 by hchereau          #+#    #+#             */
/*   Updated: 2023/01/08 16:59:49 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"






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
	free la ligne precedente
	read sur BUFFERR size
	parcourir BUFFER jusqu'a tomber sur \n
	si pas de \n:
		join la str final et le BUFFER sur une nouvelle ligne
		free la ligne precedente
	si \n:
		ajouter \n a str final
		garder en static suite BUFFER
	
	
*/
