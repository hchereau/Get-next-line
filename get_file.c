#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
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

char	*ft_strjoin(char const *s1, char const *s2)
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
char	*get_size(int	fd)
{
	size_t	bytes_count;
	size_t size_string;
	char	*string_file;
	char	part_file[BUFFER_SIZE];

	ft_bzero(part_file, BUFFER_SIZE);
	size_string = 0;
	bytes_count =read(fd, part_file, BUFFER_SIZE);
	size_string += bytes_count;
	while(bytes_count > 0)
	{
		string_file = (char *)malloc(sizeof(char) * sizestring);
		if (string_file == NULL)
			return NULL;
		else
		{
			
		}
	}
}
int main(void)
{
	int		fd;

	fd = open("readthis.txt", O_RDONLY);
	printf("%s", get_size(fd));
	close(fd);

}
