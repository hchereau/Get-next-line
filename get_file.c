#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

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

static char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size1;
	size_t	size2;
	char	*join;

	size1 = 0;
	size2 = 0;
	if (s1 != NULL)
		size1 = ft_strlen(s1);
	if (s2 != NULL)
		size2 = ft_strlen(s2);
	join = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (join != NULL)
	{
		if (s1 != NULL)
			ft_strlcpy(join, s1, size1 + 1);
		if (s2 != NULL)
			ft_strlcpy(join + size1, s2, size2 + 1);
		join[size1 + size2] = '\0';
	}
	return (join);
}

static void	*ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		++i;
	}
	return (s);
}

static void	add_str(char **s1, char *s2)
{
	char *p1;

	p1 = *s1;
	*s1 = ft_strjoin(*s1, s2);
	free(p1);
}

char	*get_file(int	fd)
{
	size_t	bytes_count;
	char	*string_file;
	char	part_file[BUFFER_SIZE + 1];

	ft_bzero(part_file, BUFFER_SIZE + 1);
	bytes_count = read(fd, part_file, BUFFER_SIZE);
	string_file = NULL;
	while(bytes_count > 0)
	{
		add_str(&string_file, part_file);
		bytes_count = read(fd, part_file, BUFFER_SIZE);
	}
	return (string_file);
}
int main(void)
{
	int		fd;
	char	*file_content;

	fd = open("readthis.txt", O_RDONLY);
	file_content = get_file(fd);
	printf("%s", file_content);
	free(file_content);	
	close(fd);
}
