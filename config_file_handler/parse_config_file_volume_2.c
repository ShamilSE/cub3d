/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_file_volume_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 22:56:21 by mismene           #+#    #+#             */
/*   Updated: 2021/02/16 22:56:23 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/cub3d.h"

void	check_color_line(char *line)
{
	char	*valid_colour_chars;
	int		i;

	valid_colour_chars = ft_strdup(" ,12345679890");
	i = 0;
	while (*line)
	{
		while (1)
		{
			if (valid_colour_chars[i] == *line)
				break ;
			i++;
			if (i == 13)
				throw_error("invalid char(s) detected");
		}
		i = 0;
		line++;
	}
	free(valid_colour_chars);
}

void	fill_color_in_arr(int *direction, char *line)
{
	int		i;
	char	comma;
	int		comma_counter;

	comma = 'n';
	comma_counter = 0;
	check_color_line(line);
	i = 0;
	while (i < 3)
	{
		direction[i] = *line - 48;
		line++;
		while (ft_isdigit(*line))
		{
			direction[i] = (direction[i] * 10) + (*line - 48);
			line++;
		}
		while (line && !(ft_isdigit(*line)))
		{
			to_next_color_char(line, &comma_counter, &comma);
			line++;
		}
		comma = 'n';
		i++;
	}
}

void	get_color(int *direction, char *line)
{
	int		i;

	if (!(ft_isdigit(line[ft_strlen(line) - 1])))
		throw_error("unexpected symbols in resolution option");
	while (!(ft_isdigit(*line)) || *line == '-')
	{
		if (*line == '-')
			throw_error("colors must be in range: 0 - 255");
		line++;
	}
	fill_color_in_arr(direction, line);
	i = 0;
	while (i < 3)
	{
		if (direction[i] < 0 || direction[i] > 255)
			throw_error("colors must be in range: 0 - 255");
		i++;
	}
}

void	copy_north_str(char *line)
{
	if (name_checker(g_config->north, "nothing"))
	{
		free(g_config->north);
		g_config->north = ft_strdup(line);
		if ((ft_strncmp(line + ft_strlen(line) - 4, ".xpm", 4)) &&
		!(*(line + ft_strlen(line))))
			throw_error("invalid texture extension");
	}
	else
		throw_error("duplicate north texture option, leave only one");
}

void	copy_south_str(char *line)
{
	if (name_checker(g_config->south, "nothing"))
	{
		free(g_config->south);
		g_config->south = ft_strdup(line);
		if ((ft_strncmp(line + ft_strlen(line) - 4, ".xpm", 4)) &&
		!(*(line + ft_strlen(line))))
			throw_error("invalid texture extension");
	}
	else
		throw_error("duplicate south texture option, leave only one");
}
