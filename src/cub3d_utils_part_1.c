/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_part_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 19:47:11 by mismene           #+#    #+#             */
/*   Updated: 2021/02/16 19:47:14 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (str1 == NULL || str2 == NULL)
		return (1);
	while (*(str1 + i) && *(str1 + i) == *(str2 + i) && i < n - 1)
		i++;
	if (n)
		return (*(str1 + i) - *(str2 + i));
	return (0);
}

int		close_window(t_data *g_data)
{
	exit(0);
	return (0);
}

void	xpm_to_image(void)
{
	int g_width;
	int g_height;

	if (!(g_texture_north->image =
	mlx_xpm_file_to_image(g_data->mlx, g_config->north, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(g_texture_south->image =
	mlx_xpm_file_to_image(g_data->mlx, g_config->south, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(g_texture_west->image =
	mlx_xpm_file_to_image(g_data->mlx, g_config->west, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(g_texture_east->image =
	mlx_xpm_file_to_image(g_data->mlx, g_config->east, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(g_texture_sprite->image =
	mlx_xpm_file_to_image(g_data->mlx, g_config->sprite, &g_width, &g_height)))
		throw_error("invalid sprite path");
}

void	malloc_textures(void)
{
	if (!(g_texture_north = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(g_texture_south = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(g_texture_west = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(g_texture_east = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(g_texture_sprite = malloc(sizeof(t_texture))))
		throw_error("no memory");
}

void	get_textures(void)
{
	malloc_textures();
	xpm_to_image();
	g_texture_north->address = (int *)mlx_get_data_addr(g_texture_north->image,
	&g_texture_north->bpp, &g_texture_north->size, &g_texture_north->endian);
	g_texture_south->address = (int *)mlx_get_data_addr(g_texture_south->image,
	&g_texture_south->bpp, &g_texture_south->size, &g_texture_south->endian);
	g_texture_west->address = (int *)mlx_get_data_addr(g_texture_west->image,
	&g_texture_west->bpp, &g_texture_west->size, &g_texture_west->endian);
	g_texture_east->address = (int *)mlx_get_data_addr(g_texture_east->image,
	&g_texture_east->bpp, &g_texture_east->size, &g_texture_east->endian);
	g_texture_sprite->address =
			(int *)mlx_get_data_addr(g_texture_sprite->image,
	&g_texture_sprite->bpp, &g_texture_sprite->size, &g_texture_sprite->endian);
}
