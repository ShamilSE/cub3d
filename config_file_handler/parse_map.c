#include "../src/cub3d.h"

void	is_map_string_valid_helper(const char *line, char *valid_map_chars, int *i, int *j)
{
	while (valid_map_chars[*j])
	{
		if (line[*i] == 'N' || line[*i] == 'E' || line[*i] == 'W' || line[*i] == 'S')
			config->player = line[*i];
		if (line[*i] == valid_map_chars[*j])
			break ;
		if (*j == 7)
			throw_error("map is not valid");
		(*j)++;
	}
	*j = 0;
	(*i)++;
}

void	is_map_string_valid(const char *line)
{
	char	*valid_map_chars;
	int		i = 0;
	int		j = 0;

	valid_map_chars = ft_strdup(" 012NEWS");
	while (line[i])
	{
		if (line[i] == '2')
			sprites->count++;
		i++;
	}
	i = 0;
	while (line[i])
		is_map_string_valid_helper(line, valid_map_chars, &i, &j);
	free(valid_map_chars);
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

void	is_map_valid_helper_2(int **i, int **j, int **i1, int **j1)
{
	while (g_map[**i][**j1] != '1')
	{
		if (g_map[**i][**j1] == '1')
			continue ;
		if (ft_strlen(g_map[**i]) == **j1 + 1)
			throw_error("map is not valid");
		(**j1)++;
	}
	**j1 = **j;
	while (g_map[**i][**j1] != '1')
	{
		if (**j1 == 0)
			throw_error("map is not valid");
		(**j1)--;
	}
	**i1 = **i;
}

void	is_map_valid_helper(int *i, int *j, int *i1, int *j1)
{
	if (g_map[*i][*j] == '0' || g_map[*i][*j] == '2')
	{
		if (*i > 0 && *i < config->map_strings - 1)
		{
			if (*j > ft_strlen(g_map[*i - 1]) || *j > ft_strlen(g_map[*i + 1]))
				throw_error("map is not valid");
		}
		*j1 = *j;
		is_map_valid_helper_2(&i, &j, &i1, &j1);
		while (g_map[*i1][*j] != '1')
		{
			if (*i1 == 0)
				throw_error("map is not valid");
			(*i1)--;
		}
		*i1 = *i;
		while (g_map[*i1] && g_map[*i1][*j] != '1')
		{
			if ((g_map[*i1][*j] != '1') && ((*i1) == config->map_strings - 1))
				throw_error("map is not valid");
			(*i1)++;
		}
	}
}

void	is_map_valid_helper_3(int *map_i, int *i, int *j)
{
	sprites->x[*map_i] = *i + 0.5;
	sprites->y[*map_i] = *j + 0.5;
}

void	is_map_valid_helper_4(int *player_flag, int *i, int *j)
{
	*player_flag = 1;
	data->posX = *i + 0.5;
	data->posY = *j + 0.5;
	g_map[*i][*j] = '0';
}



int		is_map_valid(void)
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
	while (g_map[i])
	{
		while (g_map[i][j])
		{
			if (g_map[i][j] == '2')
			{
				sprites->x[map_i] = i + 0.5;
				sprites->y[map_i] = j + 0.5;
				map_i++;
			}
			if (g_map[i][j] == 'N' || g_map[i][j] == 'E' || g_map[i][j] == 'W' || g_map[i][j] == 'S')
			{
				if (player_flag)
					throw_error("several players on a map, leave only one");
				player_flag = 1;
				data->posX = i + 0.5;
				data->posY = j + 0.5;
				g_map[i][j] = '0';
			}
			is_map_valid_helper(&i, &j, &i1, &j1);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	parse_map_helper(void)
{

	if (!(sprites->x = malloc(sizeof(double) * sprites->count + 1)))
		throw_error("no memory");
	if (!(sprites->y = malloc(sizeof(double) * sprites->count + 1)))
		throw_error("no memory");
	sprites->x[sprites->count] = 0;
	sprites->y[sprites->count] = 0;
	if (!config->player)
		throw_error("there is no player on a map");
	if (!is_map_valid())
		throw_error("map is not valid");
}

void	parse_map_helper_2(char m_flag, char **line)
{
	if (m_flag == 'y')
		throw_error("map must contain nothing but ' 012NEWS' symbols");
	free(*line);
}

char	**parse_map_helper_3(char *filename)
{
	char	**map;

	sprites->count = 0;
	config->map_strings = count_map_strings(filename);
	if (!(map = malloc(sizeof(char *) * (config->map_strings + 1))))
		throw_error("no memory");
	return (map);
}

char	**parse_map(char *filename)
{
	int		i;
	int		fd;
	char	*line;
	char	m_flag;

	m_flag = 'n';
	fd =  open(filename, O_RDONLY);
	i = 0;
	g_map = parse_map_helper_3(filename);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '1' && *line != ' ')
		{
			parse_map_helper_2(m_flag, &line);
			continue;
		}
		else
		{
			m_flag = 'y';
			is_map_string_valid(line);
			g_map[i] = ft_strdup(line);
			i++;
			free(line);
		}
	}
	is_map_string_valid(line);
	g_map[i] = ft_strdup(line);
	free(line);
	g_map[i + 1] = 0x0;
	parse_map_helper();
	return (g_map);
}