//#include "cub3d.h"
//
//
//
//
//void	move_forward()
//{
//	info->posX += info->dirX * info->moveSpeed;
//	info->posY += info->dirY * info->moveSpeed;
//}
//
//void	move_player(int keycode, int **worldMap)
//{
//	if (keycode == 13)
//	{
//		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] &&
//			!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
//			move_forward();
//
//	}
//	//move backwards if no wall behind you
//	if (keycode == 1)
//	{
//		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
//			info->posX -= info->dirX * info->moveSpeed;
//		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
//			info->posY -= info->dirY * info->moveSpeed;
//	}
//	//rotate to the right
//	if (keycode == 2)
//	{
//		//both camera direction and camera plane must be rotated
//		double oldDirX = info->dirX;
//		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
//		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
//		double oldPlaneX = info->planeX;
//		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
//		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
//	}
//	//rotate to the left
//	if (keycode == 0)
//	{
//		//both camera direction and camera plane must be rotated
//		double oldDirX = info->dirX;
//		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
//		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
//		double oldPlaneX = info->planeX;
//		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
//		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
//	}
//	if (info->key_esc)
//		exit(0);
//}
//
////void	move_player(int keycode)
////{
////	if (keycode == 13)
////	{
////		if (all->map[(int)((player->location->y + (player->pdy * 5)) / SCALE)][(int)((player->location->x + (player->pdx * 5)) / SCALE)] == '1')
////			return ;
////		move_forward();
////	}
////	else
////	{
////		if (keycode == 1)
////		{
////			if (all->map[(int)((player->location->y - (player->pdy * 5)) / SCALE)][(int)((player->location->x - (player->pdx * 5)) / SCALE)] == '1')
////				return ;
////			move_backward();
////		}
////		if (keycode == 0)
////			look_left();
////		if (keycode == 2)
////			look_right();
////	}
////	mlx_destroy_image(all->data->mlx, all->data->image);
////}