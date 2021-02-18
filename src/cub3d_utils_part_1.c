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

	if (!(texture_north->image =
	mlx_xpm_file_to_image(g_data->mlx, config->north, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(texture_south->image =
	mlx_xpm_file_to_image(g_data->mlx, config->south, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(texture_west->image =
	mlx_xpm_file_to_image(g_data->mlx, config->west, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(texture_east->image =
	mlx_xpm_file_to_image(g_data->mlx, config->east, &g_width, &g_height)))
		throw_error("invalid texture path");
	if (!(texture_sprite->image =
	mlx_xpm_file_to_image(g_data->mlx, config->sprite, &g_width, &g_height)))
		throw_error("invalid sprite path");
}

void	malloc_textures(void)
{
	if (!(texture_north = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(texture_south = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(texture_west = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(texture_east = malloc(sizeof(t_texture))))
		throw_error("no memory");
	if (!(texture_sprite = malloc(sizeof(t_texture))))
		throw_error("no memory");
}

void	get_textures(void)
{
	malloc_textures();
	xpm_to_image();
	texture_north->address = (int *)mlx_get_data_addr(texture_north->image,
	&texture_north->bpp, &texture_north->size, &texture_north->endian);
	texture_south->address = (int *)mlx_get_data_addr(texture_south->image,
	&texture_south->bpp, &texture_south->size, &texture_south->endian);
	texture_west->address = (int *)mlx_get_data_addr(texture_west->image,
	&texture_west->bpp, &texture_west->size, &texture_west->endian);
	texture_east->address = (int *)mlx_get_data_addr(texture_east->image,
	&texture_east->bpp, &texture_east->size, &texture_east->endian);
	texture_sprite->address = (int *)mlx_get_data_addr(texture_sprite->image,
	&texture_sprite->bpp, &texture_sprite->size, &texture_sprite->endian);
}
