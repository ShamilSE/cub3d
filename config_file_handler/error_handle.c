#include "../headers/graphics.h"

t_config *config;

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
	while (!(ft_isdigit(*line)) || )
	{
		if (*line == '-')
		{
			ft_printf("Error\ncolors must be in range: 0 - 255\n");
			exit(1);
		}
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
			line++;
	}
	i = 0;
	while (i++ < 3)
		if (direction[i] < 0 || direction[i] > 255)
		{
			ft_printf("Error\ncolors must be in range: 0 - 255\n");
			exit(1);
		}
	i = 0;
	while (i < 3)
		ft_printf("%d\n", direction[i++]);
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
	{
		ft_printf("Error\nno spaces at the start of a line!\n");
		exit(1);
	}
	if (*line == 'R')
		get_resolution(line);
	else if (*line == 'F')
		get_color(config->floor, line);
	else if (*line == 'C')
		get_color(config->celling, line);
	else if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		get_filepath(line);
}

void	error_handle(char *filename)
{
	int		fd;
	char	*line;
	int		i;

	if (!(name_checker(filename, ".cub")))
	{
		ft_printf("Error\nfile extension isn't right\n");
		exit(1);
	}
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("Eroor\nthere is no such file like %s\n", filename);
		exit(1);
	}
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

int main(void){
	error_handle("map.cub");
}