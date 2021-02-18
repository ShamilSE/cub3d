/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:36:08 by mismene           #+#    #+#             */
/*   Updated: 2021/02/18 00:36:10 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/cub3d.h"

void	parse_map_helper_2(char m_flag, char **line)
{
	if (m_flag == 'y')
		throw_error("map must contain nothing but ' 012NEWS' symbols");
	free(*line);
}

char	**parse_map_helper_3(char *filename)
{
	char	**map;

	g_sprites->count = 0;
	g_config->map_strings = count_map_strings(filename);
	if (!(map = malloc(sizeof(char *) * (g_config->map_strings + 1))))
		throw_error("no memory");
	return (map);
}

void	parse_map_helper_4(char *line, char *m_flag, int *i)
{
	*m_flag = 'y';
	is_map_string_valid(line);
	g_map[*i] = ft_strdup(line);
	(*i)++;
	free(line);
}

void	handle_last_string(char *line, int *i)
{
	is_map_string_valid(line);
	g_map[*i] = ft_strdup(line);
	free(line);
}

char	**parse_map(char *filename)
{
	int		i;
	int		fd;
	char	*line;
	char	m_flag;

	m_flag = 'n';
	fd = open(filename, O_RDONLY);
	i = 0;
	g_map = parse_map_helper_3(filename);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '1' && *line != ' ')
		{
			parse_map_helper_2(m_flag, &line);
			continue;
		}
		else
			parse_map_helper_4(line, &m_flag, &i);
	}
	handle_last_string(line, &i);
	g_map[i + 1] = 0x0;
	parse_map_helper();
	free(g_map_valid);
	return (g_map);
}
