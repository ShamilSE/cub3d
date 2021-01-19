//
// Created by Shamil on 19.01.2021.
//

#include "../headers/graphics.h"

int		name_checker(char *name, char *chars)
{
	while (*name)
	{
		if (name == chars)
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

	if (name_checker(config, ".cub"))
	{
		printf("correct\n");
	}
	fd = open(config, O_RDONLY);
//	while (get_next_line(fd, &line))
//	{
//
//	}
}

int main(){
	get_options("map.cub");
}