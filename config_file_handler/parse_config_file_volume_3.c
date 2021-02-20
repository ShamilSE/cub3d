/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_file_volume_3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:00:17 by mismene           #+#    #+#             */
/*   Updated: 2021/02/16 23:00:21 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/cub3d.h"

void	copy_sprite_str(char *line)
{
	if (name_checker(g_config->sprite, "nothing"))
	{
		free(g_config->sprite);
		g_config->sprite = ft_strdup(line);
		if ((ft_strncmp(line + ft_strlen(line) - 4, ".xpm", 4)) &&
		!(*(line + ft_strlen(line))))
			throw_error("invalid sprite extension");
	}
	else
		throw_error("duplicate sprite texture option, leave only one");
}

void	copy_west_str(char *line)
{
	if (name_checker(g_config->west, "nothing"))
	{
		free(g_config->west);
		g_config->west = ft_strdup(line);
		if ((ft_strncmp(line + ft_strlen(line) - 4, ".xpm", 4)) &&
		!(*(line + ft_strlen(line))))
			throw_error("invalid texture extension");
	}
	else
		throw_error("duplicate west texture option, leave only one");
}

void	copy_east_str(char *line)
{
	if (name_checker(g_config->east, "nothing"))
	{
		free(g_config->east);
		g_config->east = ft_strdup(line);
		if ((ft_strncmp(line + ft_strlen(line) - 4, ".xpm", 4)) &&
		!(*(line + ft_strlen(line))))
			throw_error("invalid texture extension");
	}
	else
		throw_error("duplicate east texture, leave only one");
}

void	sprites_router(char c, char c2, char *line)
{
	if (c == 'N')
		copy_north_str(line);
	else if (c == 'S' && c2 == 'O')
		copy_south_str(line);
	else if (c == 'S')
		copy_sprite_str(line);
	else if (c == 'W')
		copy_east_str(line);
	else if (c == 'E')
		copy_west_str(line);
	else
		throw_error("invalid option1");
}

void	get_filepath(char *line)
{
	char	c;
	char	c2;
	char	c3;

	c = *line;
	line++;
	c2 = *line;
	c3 = *(line + 1);
	if (c3 != ' ' && c3 != '/' && c3 != '.')
		throw_error("invalid option2");
	if (c2 != ' ' && c == 'S' && c2 != 'O')
		throw_error("invalid option3");
	while (*line != '/')
	{
		if (*line == '.')
			break ;
		line++;
	}
	sprites_router(c, c2, line);
}
