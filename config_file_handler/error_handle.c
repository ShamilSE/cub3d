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

void	first_char(char *line)
{
	int		option;

	option = 0;
	if (*line == ' ')
	{
		ft_printf("Error\nno spaces at the start of a line!\n");
		exit(1);
	}
	if (*line == 'R')
		option = 1;
	else if (*line == 'F')
		option = 2;
	else if (*line == '.')
		option = 3;
	line++;
	while (*line == ' ')
		line++;
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