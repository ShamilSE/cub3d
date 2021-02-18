/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_volume_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:43:16 by mismene           #+#    #+#             */
/*   Updated: 2021/02/18 00:43:21 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/cub3d.h"

void	is_map_valid_helper(int *i, int *j, int *i1, int *j1)
{
	if (g_map[*i][*j] == '0' || g_map[*i][*j] == '2')
	{
		if (*i > 0 && *i < config->map_strings - 1)
		{
			if (*j > ft_strlen(g_map[*i - 1]) || *j > ft_strlen(g_map[*i + 1]))
				throw_error("map is not valid");
		}
		*j1 = *j;
		is_map_valid_helper_2(&i, &j, &i1, &j1);
		while (g_map[*i1][*j] != '1')
		{
			if (*i1 == 0)
				throw_error("map is not valid");
			(*i1)--;
		}
		*i1 = *i;
		while (g_map[*i1] && g_map[*i1][*j] != '1')
		{
			if ((g_map[*i1][*j] != '1') && ((*i1) == config->map_strings - 1))
				throw_error("map is not valid");
			(*i1)++;
		}
	}
}

void	map_valid_init(void)
{
	map_valid = malloc(sizeof(t_map_valid));
	map_valid->map_i = 0;
	map_valid->player_flag = 0;
	map_valid->i = 0;
	map_valid->j = 0;
}

void	is_map_valid_helper_3(void)
{
	if (map_valid->player_flag)
		throw_error("several players on a map, leave only one");
	map_valid->player_flag = 1;
	data->pos_x = map_valid->i + 0.5;
	data->pos_y = map_valid->j + 0.5;
	g_map[map_valid->i][map_valid->j] = '0';
}

int		is_map_valid(void)
{
	map_valid_init();
	while (g_map[map_valid->i])
	{
		while (g_map[map_valid->i][map_valid->j])
		{
			if (g_map[map_valid->i][map_valid->j] == '2')
			{
				sprites->x[map_valid->map_i] = map_valid->i + 0.5;
				sprites->y[map_valid->map_i] = map_valid->j + 0.5;
				map_valid->map_i++;
			}
			if (g_map[map_valid->i][map_valid->j] == 'N' ||
				g_map[map_valid->i][map_valid->j] == 'E' ||
				g_map[map_valid->i][map_valid->j] == 'W' ||
				g_map[map_valid->i][map_valid->j] == 'S')
				is_map_valid_helper_3();
			is_map_valid_helper(&map_valid->i,
								&map_valid->j, &map_valid->i1, &map_valid->j1);
			map_valid->j++;
		}
		map_valid->j = 0;
		map_valid->i++;
	}
	return (1);
}

void	parse_map_helper(void)
{
	if (!(sprites->x = malloc(sizeof(double) * sprites->count + 1)))
		throw_error("no memory");
	if (!(sprites->y = malloc(sizeof(double) * sprites->count + 1)))
		throw_error("no memory");
	sprites->x[sprites->count] = 0;
	sprites->y[sprites->count] = 0;
	if (!config->player)
		throw_error("there is no player on a map");
	if (!is_map_valid())
		throw_error("map is not valid");
}
