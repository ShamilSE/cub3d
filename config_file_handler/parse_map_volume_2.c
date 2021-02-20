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

void	is_map_valid_helper(unsigned int *i,
unsigned int *j, unsigned int *i1, unsigned int *j1)
{
	if (g_map[*i][*j] == '0' || g_map[*i][*j] == '2')
	{
		if (*i > 0 && *i < g_config->map_strings - 1)
		{
			if (*j > ft_strlen(g_map[*i - 1]) || *j > ft_strlen(g_map[*i + 1]))
				throw_error("map is not valid1");
		}
		*j1 = *j;
		is_map_valid_helper_2(&i, &j, &i1, &j1);
		while (g_map[*i1][*j] != '1')
		{
			if (*i1 == 0)
				throw_error("map is not valid2");
			(*i1)--;
		}
		*i1 = *i;
		while (g_map[*i1] && g_map[*i1][*j] != '1')
		{
			if ((g_map[*i1][*j] != '1') && ((*i1) == g_config->map_strings - 1))
				throw_error("map is not valid3");
			(*i1)++;
		}
	}
}

void	map_valid_init(void)
{
	if (!(g_map_valid = malloc(sizeof(t_map_valid))))
		throw_error("no memory");
	g_map_valid->map_i = 0;
	g_map_valid->player_flag = 0;
	g_map_valid->i = 0;
	g_map_valid->j = 0;
}

void	is_map_valid_helper_3(void)
{
	if (g_map_valid->player_flag)
		throw_error("several players on a map, leave only one");
	g_map_valid->player_flag = 1;
	g_data->pos_x = g_map_valid->i + 0.5;
	g_data->pos_y = g_map_valid->j + 0.5;
	g_map[g_map_valid->i][g_map_valid->j] = '0';
}

int		is_map_valid(void)
{
	map_valid_init();
	while (g_map[g_map_valid->i])
	{
		while (g_map[g_map_valid->i][g_map_valid->j])
		{
			if (g_map[g_map_valid->i][g_map_valid->j] == '2')
			{
				g_sprites->x[g_map_valid->map_i] = g_map_valid->i + 0.5;
				g_sprites->y[g_map_valid->map_i] = g_map_valid->j + 0.5;
				g_map_valid->map_i++;
			}
			if (g_map[g_map_valid->i][g_map_valid->j] == 'N' ||
				g_map[g_map_valid->i][g_map_valid->j] == 'E' ||
				g_map[g_map_valid->i][g_map_valid->j] == 'W' ||
				g_map[g_map_valid->i][g_map_valid->j] == 'S')
				is_map_valid_helper_3();
			is_map_valid_helper(&g_map_valid->i,
			&g_map_valid->j, &g_map_valid->i1, &g_map_valid->j1);
			g_map_valid->j++;
		}
		g_map_valid->j = 0;
		g_map_valid->i++;
	}
	return (1);
}

void	parse_map_helper(void)
{
	if (!(g_sprites->x = malloc(sizeof(double) * g_sprites->count + 1)))
		throw_error("no memory");
	if (!(g_sprites->y = malloc(sizeof(double) * g_sprites->count + 1)))
		throw_error("no memory");
	g_sprites->x[g_sprites->count] = 0;
	g_sprites->y[g_sprites->count] = 0;
	if (g_config->player != 'N' && g_config->player != 'E' &&
	g_config->player != 'W' && g_config->player != 'S')
		throw_error("there is no player on a map");
	if (!is_map_valid())
		throw_error("map is not valid4");
}
