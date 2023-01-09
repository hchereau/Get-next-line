/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:46:10 by hchereau          #+#    #+#             */
/*   Updated: 2023/01/09 16:33:57 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		++len;
	return (len);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size > 0)
	{
		i = 0;
		while (i < size - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t size)
{
	size_t	size1;
	char	*join;

	size1 = 0;
	if (s1 != NULL)
		size1 = ft_strlen(s1);
	join = (char *)malloc((size1 + size + 1) * sizeof(char));
	if (join != NULL)
	{
		if (s1 != NULL)
			ft_strlcpy(join, s1, size1 + 1);
		if (s2 != NULL)
			ft_strlcpy(join + size1, s2, size);
		join[size1 + size] = '\0';
	}
	return (join);
}

void	add_str(char **s1, char *s2, size_t size)
{
	char *p1;

	p1 = *s1;
	*s1 = ft_strnjoin(*s1, s2, size);
	free(p1);
}
