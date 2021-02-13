#include "../headers/graphics.h"

t_config *config;

void	throw_error(char *error_message)
{
	ft_printf("Error\n%s\n", error_message);
	exit(0);
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
	if (*line == '-')
		throw_error("resolution must be positive");
	while (ft_isdigit(*line))
	{
		config->s_width = (config->s_width * 10) + (*line - 48);
		line++;
	}
	while (*line == ' ')
		line++;
	while (ft_isdigit(*line))
	{
		config->s_height = (config->s_height * 10) + (*line - 48);
		line++;
	}
}

void	get_color(int *direction, char *line)
{
	int		i;
	char	comma;

	i = 0;
	comma = 'n';
	while (!(ft_isdigit(*line)) || *line == '-')
	{
		if (*line == '-')
			throw_error("colors must be in range: 0 - 255\n");
		line++;
	}
	while (i < 3)
	{
		direction[i] = *line - 48;
		line++;
		while (ft_isdigit(*line))
		{
			direction[i] = (direction[i] * 10) + (*line - 48);
			line++;
		}
		i++;
		while (line && !(ft_isdigit(*line)))
		{
			if (comma == 'y')
				throw_error("suka");
			if (*line != ',' && ft_isdigit(*line))
				throw_error("invalid char(s) in color option");
			else if (*line == ',')
				comma = 'y';
			line++;
		}
		comma = 'n';
	}
	i = 0;
	while (i++ < 3)
		if (direction[i] < 0 || direction[i] > 255)
			throw_error("colors must be in range: 0 - 255\n");
}

void	get_filepath(char *line)
{
	char	c;
	char	c2;

	c = *line;
	line++;
	c2 = *line;
	while (*line != '/')
		line++;
	if (c == 'N')
	{
		if (name_checker(config->north, "nothing"))
		{
			free(config->north);
			config->north = ft_strdup(line);
		}
		else
			throw_error("duplicate north texture option, leave only one");
	}
	else if (c == 'S' && c2 == 'O') {
		if (name_checker(config->south, "nothing"))
		{
			free(config->south);
			config->south = ft_strdup(line);
		}
		else
			throw_error("duplicate south texture option, leave only one");
	}
	else if (c == 'S')
	{
		if (name_checker(config->sprite, "nothing"))
		{
			free(config->sprite);
			config->sprite = ft_strdup(line);
		}
		else
			throw_error("duplicate sprite texture option, leave only one");
	}
	else if (c == 'W')
	{
		if (name_checker(config->west, "nothing"))
		{
			free(config->west);
			config->west = ft_strdup(line);
		}
		else
 			throw_error("duplicate west texture option, leave only one");
	}
	else if (c == 'E')
	{
		if (name_checker(config->east, "nothing"))
		{
			free(config->east);
			config->east = ft_strdup(line);
		}
		else
			throw_error("duplicate east texture, leave only one");
	}
}

void	config_init()
{
	config = malloc(sizeof(t_config));
	config->s_width = 0;
	config->s_height = 0;
	config->floor[0] = -1933;
	config->floor[1] = -1933;
	config->floor[2] = -1933;
	config->celling[0] = -1933;
	config->celling[1] = -1933;
	config->celling[2] = -1933;
	config->north = ft_strdup("nothing");
	config->east = ft_strdup("nothing");
	config->west = ft_strdup("nothing");
	config->south = ft_strdup("nothing");
	config->sprite = ft_strdup("nothing");
}

void	first_char(char *line)
{
	char	*lp;
	char	valid_chars[10] = " RNEWSFC1";

	if (!(ft_strchr(valid_chars, line[0])))
		throw_error("delete invalid char(s)");
	lp = line;
	if (*line == ' ')
	{
		while (lp++)
			if (*lp == '1')
				break ;
		if (lp == NULL)
			throw_error("delete spaces before string\n");
	}
	if (*line == 'R')
	{
		if (config->s_width)
			throw_error("duplicate resolution option, leave only one");
		get_resolution(line);
	}
	else if (*line == 'F')
	{
		if (config->floor[2] == -1933)
			get_color(config->floor, line);
		else
			throw_error("duplicate floor color option, leave only one");
	}
	else if (*line == 'C')
	{
		if (config->celling[2] == -1933)
			get_color(config->celling, line);
		else
			throw_error("duplicate celling option, please only one");
	}
	else if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		get_filepath(line);
}

void completeness_check()
{
	if (config->floor[2] == -1933 ||
	config->celling[2] == -1933 ||
	name_checker(config->north, "nothing") ||
	name_checker(config->east, "nothing") ||
	name_checker(config->west, "nothing") ||
	name_checker(config->south, "nothing"))
		throw_error("config isn't completed");
}

void	parse_config_file(char *filename)
{
	int		fd;
	char	*line;
	int		i;
	char	**map;

	config_init();
	config->filename = ft_strdup(filename);
	if (!(name_checker(filename, ".cub")))
		throw_error("config file must have '.cub' extension");
	if ((fd = open("map.cub", O_RDONLY)) < 0)
		throw_error("invalid filename\n");
	while ((i = get_next_line(fd, &line)))
	{
		first_char(line);
		if (*line == '1')
			break;
		free(line);
	}
	config->map = parse_map(filename);
	if (!(ft_strchr(line, '1')))
		throw_error("1");
	free(line);
	completeness_check();
}