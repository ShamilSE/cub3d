#include "../src/cub3d.h"

void	is_map_string_valid(const char *line)
{
	char	valid_map_chars[9] = " 012NEWS";
	int		i = 0;
	int		j = 0;

	while (line[i])
	{
		if (line[i] == '2')
			sprites->count++;
		i++;
	}
	i = 0;
	while (line[i])
	{
		while (valid_map_chars[j])
		{
			if (line[i] == 'N' || line[i] == 'E' || line[i] == 'W' || line[i] == 'S')
				config->player = line[i];
			if (line[i] == valid_map_chars[j])
				break ;
			if (j == 7)
			{
				printf("%s\n", line);
				throw_error("map is not valid7");
			}
			j++;
		}
		j = 0;
		i++;
	}
}

int		is_map_valid(char **map)
{
	int	i;
	int	j;
	int	j1;
	int	i1;
	int		player_flag;
	int	map_i;

	map_i = 0;
	player_flag = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				sprites->x[map_i] = i + 0.5;
				sprites->y[map_i] = j + 0.5;
				map_i++;
			}
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S')
			{
				if (player_flag)
					throw_error("several players on a map, leave only one");
				player_flag = 1;
				data->posX = i + 0.5;
				data->posY = j + 0.5;
				map[i][j] = '0';
			}
			if (map[i][j] == '0' || map[i][j] == '2')
			{
				if (i > 0 && i < config->map_strings - 1)
				{
					if (j > ft_strlen(map[i - 1]) || j > ft_strlen(map[i + 1]))
						throw_error("map is not valid5");
				}
				j1 = j;
				while (map[i][j1] != '1')
				{
					if (map[i][j1] == '1')
						continue ;
					if (ft_strlen(map[i]) == j1 + 1)
						throw_error("map is not valid4");
					j1++;
				}
				j1 = j;
				while (map[i][j1] != '1')
				{
					if (j1 == 0)
						throw_error("map is not valid3");
					j1--;
				}
				i1 = i;
				while (map[i1][j] != '1')
				{
					if (i1 == 0)
						throw_error("map is not valid2");
					i1--;
				}
				i1 = i;
				while (map[i1] && map[i1][j] != '1')
				{
					if ((map[i1][j] != '1') && ((i1) == config->map_strings - 1))
						throw_error("map is not valid1");
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

	map_length = 0;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == '1' || *line == ' ')
			map_length++;
		free(line);
	}
	if (*line == '1' || *line == ' ')
		map_length++;
	free(line);
	return (map_length);
}

char	**parse_map(char *filename)
{
	char	**map;
	int		i;
	int		fd;
	char	*line;
	char	m_flag;

	sprites->count = 0;
	m_flag = 'n';
	fd =  open(filename, O_RDONLY);
	i = 0;
	config->map_strings = count_map_strings(filename);
	if (!(map = malloc(sizeof(char *) * (config->map_strings + 1)))) {
		throw_error("no memory");
	}
//	while (1) {}
	// leaks after this comment
	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '1' && *line != ' ')
		{
			if (m_flag == 'y') {
				throw_error("map must contain nothing but ' 012NEWS' symbols");
			}
			free(line);
			continue;
		}
		else
		{
			m_flag = 'y';
			is_map_string_valid(line);
			map[i] = ft_strdup(line);
			i++;
			free(line);
		}
	}
	is_map_string_valid(line);
	map[i] = ft_strdup(line);
	free(line);
//	leaks before this comment
			if (!(sprites->x = malloc(sizeof(double) * sprites->count + 1))) {
				throw_error("no memory");
			}
			if (!(sprites->y = malloc(sizeof(double) * sprites->count + 1))) {
				throw_error("no memory");
			}
			sprites->x[sprites->count] = 0;
			sprites->y[sprites->count] = 0;
	if (!config->player)
		throw_error("there is no player on a map");
	map[i + 1] = 0x0;
	if (!is_map_valid(map))
		throw_error("map is not valid");
	return (map);
}