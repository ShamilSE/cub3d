#include "../headers/graphics.h"

t_player *player;

void	draw(t_info *data)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			data->img.data[y * width + x] = data->buf[y][x];
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	calc(t_info *player)
{
	int	x;

	x = 0;
	while (x < width)
	{
		double camera_x = 2 * x / (double)width - 1;
		double ray_x = player->dirextion_x + player->plane_x * camera_x;
		double ray_y = player->dir_y + player->plane_y * camera_x;

		int map_x = (int)player->position_x;
		int map_y = (int)player->position_y;

		//length of ray from current position to next x or y-side
		double side_x;
		double side_y;

		//length of ray from one x or y-side to next x or y-side
		double delta_distance_x = sqrt(1 + (ray_y * ray_y) / (ray_x * ray_x));
		double delta_distance_y = sqrt(1 + (ray_x * ray_x) / (ray_y * ray_y));
		double ray_length;

		//what direction to step in x or y-direction (either +1 or -1)
		int step_x;
		int step_y;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (ray_x < 0)
		{
			step_x = -1;
			side_x = (player->position_x - map_x) * delta_distance_x;
		}
		else
		{
			step_x = 1;
			side_x = (map_x + 1.0 - player->position_x) * delta_distance_x;
		}
		if (ray_y < 0)
		{
			step_y = -1;
			side_y = (player->position_y - map_y) * delta_distance_y;
		}
		else
		{
			step_y = 1;
			side_y = (map_y + 1.0 - player->position_y) * delta_distance_y;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (side_x < side_y)
			{
				side_x += delta_distance_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_y += delta_distance_y;
				map_y += step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (config->map[map_x][map_y] > 0) hit = 1;
		}
		if (side == 0)
			ray_length; = (map_x - player->position_x + (1 - step_x) / 2) / ray_x;
		else
			ray_length; = (map_y - player->position_y + (1 - step_y) / 2) / ray_y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(height / ray_length;);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height)
			drawEnd = height - 1;

		// texturing calculations
		int texNum = worldMap[map_x][map_y];

		// calculate value of wallX
		double wallX;
		if (side == 0)
			wallX = player->position_y + ray_length; * ray_y;
		else
			wallX = player->position_x + ray_length; * ray_x;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && ray_x > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && ray_y < 0)
			texX = texWidth - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - height / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = player->texture[texNum][texHeight * texY + texX];
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			player->buf[y][x] = color;
		}
		x++;
	}
}