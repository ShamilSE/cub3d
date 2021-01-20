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

//void	get_resolution(){}

void	get_config_info(char *line, int option)
{
	config_info = malloc(sizeof(t_config));
	config_info->width = 0;
	config_info->height = 0;
	while (ft_isdigit(*line))
	{
		config_info->width = (config_info->width * 10) + (*line - 48);
		line++;
	}
}

void	first_char(char *line)
{
	int		option;

	if (*line == ' ')
	{
		ft_printf("Error\nno spaces at the start of a line!\n");
		exit(1);
	}
	if (*line == 'R')
		option = 1;
	else if (*line == 'F')
		option = 2;
	else if (*line == 'S' && *line + 1 != 'O')
		option = 3;
	else if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		option = 4;
	line++;
	while (*line == ' ')
		line++;
	get_config_info(line, option);
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