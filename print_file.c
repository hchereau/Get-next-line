#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

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

void	print_file(int fd)
{
	size_t	bytes_count;
	char	part_file[BUFFER_SIZE];

	ft_bzero(part_file, BUFFER_SIZE);
	bytes_count = read(fd, part_file, BUFFER_SIZE);
	while (bytes_count > 0)
	{
		printf("%s", part_file);
		ft_bzero(part_file, BUFFER_SIZE);
		bytes_count = read(fd, part_file, BUFFER_SIZE);
	}
}
/*
int main(void)
{
	int fd;

	fd = open("readthis.txt", O_RDONLY);
	print_file(fd);
	close(fd);

}
*/
/*
process:
	-> initialiser bytes_count
	-> initialiser part_file
	-> read sur bytes count
	-> while bytes_count > 0
		-> printf(part_file)
		-> read bytes count
*/
