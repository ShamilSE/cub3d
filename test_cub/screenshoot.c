#include "../headers/graphics.h"
#include "../test_cub/cub3d.h"

void	screenshot()
{
	int	fd;

	bmp = malloc(sizeof(t_bmp));
	if (!fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666))
		throw_error("can't create screenshot");
	bmp->file_type[0] = 'B';
	bmp->file_type[1] = 'M';
	bmp->file_size = (config->s_width * config->s_height * 4) + 54;
	bmp->reserved_bytes = 0;
	bmp->data_offset = 54;
	bmp->second_header_size = 40;
	bmp->img_width = config->s_width;
	bmp->img_height = config->s_height;
	bmp->planes = 1;
	bmp->bpp = 32;
	bmp->compression = 0;
	bmp->img_size = config->s_width * config->s_height * 4;
	bmp->x_pixels_per_meter = 2835;
	bmp->y_pixels_per_meter = 2835;
	bmp->total_colors = 0;
	bmp->important_colors = 0;

	write(fd, bmp->file_type, 2);
	write(fd, bmp->file_size, 4);
	write(fd, bmp->reserved_bytes, 4);
	write(fd, bmp->data_offset, 4);
	write(fd, bmp->second_header_size, 4);
	write(fd, bmp->img_width, 4);
	write(fd, bmp->img_height, 4);
	write(fd, bmp->planes, 2);
	write(fd, bmp->bpp, 2);
	write(fd, bmp->compression, 4);
	write(fd, bmp->img_size, 4);
	write(fd, bmp->x_pixels_per_meter, 4);
	write(fd, bmp->y_pixels_per_meter, 4);
	write(fd, bmp->total_colors, 4);
	write(fd, bmp->important_colors, 4);

	for (int i = 0; i < bmp->img_size; ++i) {
		
	}
	
}