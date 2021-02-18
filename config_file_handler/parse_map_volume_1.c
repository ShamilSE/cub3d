/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_volume_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:43:09 by mismene           #+#    #+#             */
/*   Updated: 2021/02/18 00:43:12 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/cub3d.h"

void	is_map_string_valid_helper(const char
	*line, char *valid_map_chars, int *i, int *j)
{
	while (valid_map_chars[*j])
	{
		if (line[*i] == 'N' || line[*i] ==
		'E' || line[*i] == 'W' || line[*i] == 'S')
			g_config->player = line[*i];
		if (line[*i] == valid_map_chars[*j])
			break ;
		if (*j == 7)
			throw_error("map is not valid");
		(*j)++;
	}
	*j = 0;
	(*i)++;
}

void	is_map_string_valid(const char *line)
{
	char	*valid_map_chars;
	int		i;
	int		j;

	i = 0;
	j = 0;
	valid_map_chars = ft_strdup(" 012NEWS");
	while (line[i])
	{
		if (line[i] == '2')
			g_sprites->count++;
		i++;
	}
	i = 0;
	while (line[i])
		is_map_string_valid_helper(line, valid_map_chars, &i, &j);
	free(valid_map_chars);
}

size_t	count_map_strings(char *str)
{
	int		fd;
	size_t	map_length;
	char	*line;

	map_length = 0;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == '1' || *line == ' ')
			map_length++;
		free(line);
	}
	if (*line == '1' || *line == ' ')
		map_length++;
	free(line);
	return (map_length);
}

void	is_map_valid_helper_2(int **i, int **j, int **i1, int **j1)
{
	while (g_map[**i][**j1] != '1')
	{
		if (g_map[**i][**j1] == '1')
			continue ;
		if (ft_strlen(g_map[**i]) == **j1 + 1)
			throw_error("map is not valid");
		(**j1)++;
	}
	**j1 = **j;
	while (g_map[**i][**j1] != '1')
	{
		if (**j1 == 0)
			throw_error("map is not valid");
		(**j1)--;
	}
	**i1 = **i;
}
