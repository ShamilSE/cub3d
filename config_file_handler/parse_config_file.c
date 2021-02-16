/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 22:46:18 by mismene           #+#    #+#             */
/*   Updated: 2021/02/16 22:46:35 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/cub3d.h"

void	config_init(void)
{
	if (!(config = malloc(sizeof(t_config))))
		throw_error("no memory");
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

void	config_router(char *line)
{
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
	config_router(line);
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
			break ;
		free(line);
	}
	config->map = parse_map(filename);
	if (!(ft_strchr(line, '1')))
		throw_error("1");
	free(line);
	completeness_check();
}
