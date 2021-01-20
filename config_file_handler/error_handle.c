#include "../headers/graphics.h"

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
		config_info->width = (config_info->width * 10) + (*line - 48);
		line++;
	}
	while (*line == ' ')
		line++;
	while (ft_isdigit(*line))
	{
		config_info->height = (config_info->height * 10) + (*line - 48);
		line++;
	}
}

void	get_color(char *line)
{
	ft_printf("line with color: %s\n", line);
}

void	get_filepath(char *line)
{
	ft_printf("filepath line: %s\n", line);
	char	c;
	char	c2;

	c = *line;
	line++;
	c2 = *line;
	while (*line == ' ')
		line++;
	if (c == 'N')
		config_info->north = ft_strdup(line);
	else if (c == 'S' && c2 == 'O')
		config_info->south = ft_strdup(line);
	else if (c == 'S')
		config_info->sprite = ft_strdup(line);
	else if (c == 'W')
		config_info->west = ft_strdup(line);
	else if (c == 'E')
		config_info->east =ft_strdup(line);
}

void	first_char(char *line)
{
	config_info = malloc(sizeof(t_config));
	config_info->width = 0;
	config_info->height = 0;
	if (*line == ' ')
	{
		ft_printf("Error\nno spaces at the start of a line!\n");
		exit(1);
	}
	if (*line == 'R')
		get_resolution(line);
	else if (*line == 'F' || *line == 'C')
		get_color(line);
	else if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		get_filepath(line);
}

void	error_handle(char *config)
{
	int		fd;
	char	*line;
	int		i;

	if (!(name_checker(config, ".cub")))
	{
		ft_printf("Error\nfile extension isn't right\n");
		exit(1);
	}
	fd = open(config, O_RDONLY);
	while ((i = get_next_line(fd, &line)))
	{
		first_char(line);
		if (line[ft_strlen(line) - 1] == ' ')
		{
			ft_printf("Error\nno spaces at the end of a line\n");
			exit(1);
		}
		free(line);
	}
	if (!(ft_strchr(line, '1')))
	{
		ft_printf("Error\nyou need to delete '\\n' character from last string\n");
		exit(1);
	}
	free(line);
}

int main(){
	error_handle("map.cub");
}