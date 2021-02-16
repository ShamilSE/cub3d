/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_file_volume_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 22:52:19 by mismene           #+#    #+#             */
/*   Updated: 2021/02/16 22:52:23 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/cub3d.h"

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

void	is_resolution_correct(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '-')
		throw_error("resolution must be positive");
	while (ft_isdigit(*line))
	{
		config->s_width = (config->s_width * 10) + (*line - 48);
		line++;
	}
	while (!(ft_isdigit(*line)))
	{
		if (*line == '-')
			throw_error("resolution must be positive");
		line++;
	}
	while (ft_isdigit(*line))
	{
		config->s_height = (config->s_height * 10) + (*line - 48);
		line++;
	}
}

void	get_resolution(char *line)
{
	char	*c_line;
	int		counter;

	counter = 0;
	c_line = line;
	if (!(ft_isdigit(line[ft_strlen(line) - 1])))
		throw_error("unexpected symbols in resolution option");
	while (*c_line != 0)
	{
		if (ft_isdigit(*c_line))
			counter++;
		if (*c_line == ' ')
			counter = 0;
		if (counter > 4)
			scale_reso();
		c_line++;
	}
	line++;
	is_resolution_correct(line);
}

void	to_next_color_char(char *line)
{
	if (*line == ',')
		comma_counter++;
	if (comma_counter > 2)
		throw_error("unexpected char(s) detected");
	if (g_comma == 'y')
		throw_error("unexpected char(s) detected");
	if (*line != ',' && ft_isdigit(*line))
		throw_error("invalid char(s) in color option");
	else if (*line == ',')
		g_comma = 'y';
}