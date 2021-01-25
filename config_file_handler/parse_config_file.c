#include "../headers/graphics.h"

t_config *config;

void	throw_error(char *error_message)
{
	ft_printf("Error\n%s\n", error_message);
	exit(1);
}

int		name_checker(char *name, char *chars)
{
	while (*name)
	{
		if (*name == *chars)
		{
			while (*chars++ == *name++)
				if (*name == '\0' || *chars == '\0')
					break ;
			if (*chars == '\0' && *name == '\0')
				return (1);
		}
		name++;
	}
	return (0);
}

void	get_resolution(char *line)
{
	line++;
	while (*line == ' ')
		line++;
	while (ft_isdigit(*line))
	{
		config->width = (config->width * 10) + (*line - 48);
		line++;
	}
	while (*line == ' ')
		line++;
	while (ft_isdigit(*line))
	{
		config->height = (config->height * 10) + (*line - 48);
		line++;
	}
}

void	get_color(int *direction, char *line)
{
	int	i;

	i = 0;
	while (!(ft_isdigit(*line)) || *line == '-')
	{
		if (*line == '-')
			ft_printf("5\n");
//			throw_error("colors must be in range: 0 - 255\n");
		line++;
	}
	while (i < 3)
	{
		direction[i] = *line -48;
		line++;
		while (ft_isdigit(*line))
		{
			direction[i] = (direction[i] * 10) + (*line - 48);
			line++;
		}
		i++;
		while (!(ft_isdigit(*line)))
		{
			if (*line == ' ')
				ft_printf("5\n");
//				throw_error("delete spaces between color values");
			line++;
		}
	}
	i = 0;
	while (i++ < 3)
		if (direction[i] < 0 || direction[i] > 255)
			ft_printf("6\n");
//			throw_error("colors must be in range: 0 - 255\n");
}

void	get_filepath(char *line)
{
	char	c;
	char	c2;

	c = *line;
	line++;
	c2 = *line;
	while (*line == ' ')
		line++;
	if (c == 'N')
		config->north = ft_strdup(line);
	else if (c == 'S' && c2 == 'O')
		config->south = ft_strdup(line);
	else if (c == 'S')
		config->sprite = ft_strdup(line);
	else if (c == 'W')
		config->west = ft_strdup(line);
	else if (c == 'E')
		config->east = ft_strdup(line);
}

void	config_init()
{
	config = malloc(sizeof(t_config));
	config->width = 0;
	config->height = 0;
}

void	first_char(char *line)
{
	config_init();
	if (*line == ' ')
		ft_printf("4\n");
//		throw_error("delete spaces before string\n");
	if (*line == 'R')
		get_resolution(line);
	else if (*line == 'F')
		get_color(config->floor, line);
	else if (*line == 'C')
		get_color(config->celling, line);
	else if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		get_filepath(line);
}

char	**parse_config_file(char *filename)
{
	int		fd;
	char	*line;
	int		i;
	char	**map;

	if (!(name_checker(filename, ".cub")))
		throw_error("config file must have '.cub' extension");
	if ((fd = open("map.cub", O_RDONLY)) < 0)
		throw_error("invalid filename\n");
	while ((i = get_next_line(fd, &line)))
	{
		first_char(line);
		if (*line == '1')
			break;
		if (line[ft_strlen(line) - 1] == ' ')
			ft_printf("2\n");
//			throw_error("delete spaces after string\n");
		free(line);
	}
	map = parse_map(filename);
	if (!(ft_strchr(line, '1')))
		ft_printf("3\n");
//		throw_error("1");
	free(line);
	return (map);
}
