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
		g_config->s_width = (g_config->s_width * 10) + (*line - 48);
		is_screen_size_correct();
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
		g_config->s_height = (g_config->s_height * 10) + (*line - 48);
		is_screen_size_correct();
		line++;
	}
}

void	get_resolution(char *line)
{
	if (!(ft_isdigit(line[ft_strlen(line) - 1])))
		throw_error("unexpected symbols in resolution option");
	line++;
	is_resolution_correct(line);
}

void	to_next_color_char(char *line, int *comma_counter, char *comma)
{
	if (*line == ',')
		(*comma_counter)++;
	if (*comma_counter > 2)
		throw_error("unexpected char(s) detected");
	if (*comma == 'y')
		throw_error("unexpected char(s) detected");
	if (*line != ',' && ft_isdigit(*line))
		throw_error("invalid char(s) in color option");
	else if (*line == ',')
		*comma = 'y';
}
