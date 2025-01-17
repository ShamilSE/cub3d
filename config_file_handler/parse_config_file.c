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
	if (!(g_config = malloc(sizeof(t_config))))
		throw_error("no memory");
	g_config->s_width = 0;
	g_config->s_height = 0;
	g_config->floor[0] = -1933;
	g_config->floor[1] = -1933;
	g_config->floor[2] = -1933;
	g_config->celling[0] = -1933;
	g_config->celling[1] = -1933;
	g_config->celling[2] = -1933;
	g_config->north = ft_strdup("nothing");
	g_config->east = ft_strdup("nothing");
	g_config->west = ft_strdup("nothing");
	g_config->south = ft_strdup("nothing");
	g_config->sprite = ft_strdup("nothing");
}

void	config_router(char *line)
{
	if (*line == 'R')
	{
		if (g_config->s_width)
			throw_error("duplicate resolution option, leave only one");
		get_resolution(line);
	}
	else if (*line == 'F')
	{
		if (g_config->floor[2] == -1933)
			get_color(g_config->floor, line);
		else
			throw_error("duplicate floor color option, leave only one");
	}
	else if (*line == 'C')
	{
		if (g_config->celling[2] == -1933)
			get_color(g_config->celling, line);
		else
			throw_error("duplicate celling option, please only one");
	}
	else if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		get_filepath(line);
}

void	first_char(char *line)
{
	char	*lp;
	char	*valid_chars;

	if (*line == ' ' && !ft_strchr(line, '1'))
		throw_error("config!");
	valid_chars = ft_strdup(" RNEWSFC1");
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
	free(valid_chars);
}

void	completeness_check(void)
{
	if (g_config->floor[2] == -1933 ||
	g_config->celling[2] == -1933 ||
	name_checker(g_config->north, "nothing") ||
	name_checker(g_config->east, "nothing") ||
	name_checker(g_config->west, "nothing") ||
	name_checker(g_config->south, "nothing"))
		throw_error("config isn't completed");
}

void	parse_config_file(char *filename)
{
	int		fd;
	char	*line;
	int		i;

	config_init();
	g_config->filename = ft_strdup(filename);
	if (!(name_checker(filename, ".cub")) ||
	(filename[ft_strlen(filename) - 4] != '.'))
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
	g_config->map = parse_map(filename);
	if (!(ft_strchr(line, '1')))
		throw_error("1");
	free(line);
	completeness_check();
}
