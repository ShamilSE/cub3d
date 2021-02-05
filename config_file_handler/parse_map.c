#include "../headers/graphics.h"
#include "../test_cub/cub3d.h"

void	check_map_line(char *line)
{
	if (ft_strchr(line, ' '))
		throw_error("extra symbols in map");
}

int		is_map_valid(char **map)
{
	int	i;
	int	j;
	int	j1;
	int	i1;
	size_t  map_strings_len;

	i = 0;
	j = 0;
	map_strings_len = count_map_strings(config->filename);
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				j1 = j;
				while (map[i][j1] != '1')
				{
					size_t len;
					len = ft_strlen(map[i]);
					if (map[i][(ft_strlen(map[i]) - 1)] == '0')
						throw_error("map is not valid");
					j1++;
				}
				j1 = j;
				while (map[i][j1] != '1')
				{
					if (j1 == 0)
						throw_error("map is not valid");
					j1--;
				}
				i1 = i;
				while (map[i1][j] != '1')
				{
					if (i1 == 0)
						throw_error("map is not valid");
					i1--;
				}
				i1 = i;
				while (map[i1] && map[i1][j] != '1')
				{
					if ((map[i1][j] != '1') && ((i1) == map_strings_len - 1))
						throw_error("map is not valid");
					i1++;
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

size_t	count_map_strings(char *str)
{
	int		fd;
	size_t	map_length;
	char	*line;

	map_length = 1;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == '1' || *line == ' ')
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
			check_map_line(line);
			map[i] = ft_strdup(line);
			free(line);
			i++;
		}
	}
	map[i] = ft_strdup(line);
	free(line);
	map[i + 1] = 0x0;
	if (!is_map_valid(map))
		throw_error("map is not valid :)");
	return (map);
}