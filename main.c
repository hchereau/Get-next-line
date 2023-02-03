#include <stdlib.h>
#include "get_next_line_bonus.h"


char	*get_next_line(int fd);

void	free_strs(char **lines, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(lines[i]);
		++i;
	}
}

int	are_line_null(char **lines, int size)
{
	int	ret_val;
	int	i;

	ret_val = 0;
	i = 0;
	while (i < size)
	{
		if (lines[i] != NULL)
			ret_val = 1;
		++i;
	}
	return (ret_val);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	printf("[%s]", get_next_line(0));
/*
	int		i;
	int		fd[100];
	char	**lines;

	if (ac > 1)
	{
		i = 0;
		while (i < ac - 2)
		{
			fd[i] = open(av[i + 1], O_RDONLY);
			++i;
		}
		lines = (char **)malloc(100 * sizeof(char *));
		i = 0;
		while (i < ac - 2)
		{
			int j = 0;
			while (j < atoi(av[ac - 1]))
			{
				if (j > 0)
					free(lines[i]);
				lines[i] = get_next_line(fd[i]);
				printf("%d --> [%s]\n\n", i + 1, lines[i]);
				++j;
			}
			++i;
		}
		while (are_line_null(lines, ac - 2))
		{
			i = 0;
			while (i < ac - 2)
			{
				int j = 0;
				while (j < atoi(av[ac - 1]))
				{
					free(lines[i]);
					lines[i] = get_next_line(fd[i]);
					printf("%d --> [%s]\n\n", i + 1, lines[i]);
					++j;
				}
				++i;
			}
		}
		free(lines);
	}
*/
}
