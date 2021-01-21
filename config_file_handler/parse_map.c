#include "../headers/graphics.h"

size_t	count_map_strings(char *str)
{
	int		fd;
	size_t	map_length;
	char	*line;

	map_length = 1;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == '1')
			map_length++;
	}
	return (map_length);
}

char	**parse_map(char *filename)
{
	char	**map;
	int		i;
	int		fd;
	char	*line;

	fd =  open(filename, O_RDONLY);
	i = 0;
	map = malloc(sizeof(char *) * (count_map_strings(filename) + 1));
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == '1')
		{
			map[i] = ft_strdup(line);
			free(line);
			i++;
		}
	}
	map[i] = ft_strdup(line);
	free(line);
	map[i + 1] = 0x0;
	return (map);
}