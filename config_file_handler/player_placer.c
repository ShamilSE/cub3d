#include "../headers/graphics.h"
#include "../test_cub/cub3d.h"

void	player_direction()
{

	player_direction();
	if (config->player == 'N')
	{
		data->dirX = 0;
		data->dirY = 0;
	}
	if (config->player == 'E')
	{
		data->dirX = 1;
		data->dirY = 0;
	}
	if (config->player == 'W')
	{
		data->dirX = 1;
		data->dirY == 1;
	}
	if (config->player == 'S')
	{
		data->dirX = 0;
		data->dirY = 1;
	}
}

void	player_placer()
{
//	player_direction()

}