//
// Created by Shamil on 19.01.2021.
//

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

void	get_options(char *config)
{
	int		fd;
	char	*line;
	int		i;

	if (!(name_checker(config, ".cub")))
	{
		ft_printf("file extension isn't right\n");
		exit(1);
	}
	fd = open(config, O_RDONLY);
	get_next_line(fd, &line);
	ft_printf("%s\n", line);
	while ((i = get_next_line(fd, &line)))
	{
		ft_printf("%s\n", line);
		free(line);
	}
	if (!(ft_strchr(line, '1')))
	{
		ft_printf("you need to delete '\\n' character from last string\n");
		exit(1);
	}
	ft_printf("%s\n", line);
	free(line);
}

int main(){
	get_options("map.cub");
}