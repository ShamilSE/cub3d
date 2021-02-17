#ifndef CUB3D_H
# define CUB3D_H

#include "mlx/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/mlx.h"
#include "../headers/libft.h"
#include "../headers/ft_printf.h"
#include "../headers/get_next_line.h"
#include <fcntl.h>
#define texWidth 64
#define texHeight 64
#define BUFFER_SIZE 32

typedef struct	s_data
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	void	*image;
	char	*addr;
	int		bpp;
	int		endian;
	int		size;
	double	moveSpeed;
	double	rotSpeed;
	int		*colours;
	int		i_width;
	int		i_height;
}				t_data;

typedef struct	s_texture
{
	void		*image;
	int			*address;
	int			bpp;
	int			size;
	int			endian;
}				t_texture;

typedef struct	s_sprites
{
	double		*x;
	double		*y;
	int			count;
	double		spriteX;
	double		spriteY;
	double		invDet;
	double		transformX;
	double		transformY;
	int			spriteScreenX;
	int			spriteHeight;
	int			drawStartY;
	int			drawEndY;
	int			spriteWidth;
	int			drawStartX;
	int			drawEndX;
	int			stripe;
	int			text_x;
	int			text_y;
	double		dist_tmp;
	double		x_tmp;
	double		y_tmp;
}				t_sprites;

typedef struct	s_bpm
{
	char			file_type[2];
	unsigned int	file_size;
	unsigned int	reserved_bytes;
	unsigned int	data_offset;
	unsigned int	second_header_size;
	unsigned int	img_width;
	unsigned int	img_height;
	short			planes;
	short			bpp;
	unsigned int	compression;
	unsigned int	img_size;
	unsigned int	x_pixels_per_meter;
	unsigned int	y_pixels_per_meter;
	unsigned int	total_colors;
	unsigned int	important_colors;
}				t_bmp;

typedef struct	s_config {
	char		*filename;
	int			s_width;
	int			s_height;
	char		**map;
	int			floor[4];
	int			celling[4];
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sprite;
	char		player;
	unsigned int	map_strings;
}				t_config;

typedef struct	s_calc_vars {
	int			draw_start;
	int			draw_end;
	int			side;
	int			stepX;
	int			stepY;
	int			text_x;
	int			text_y;
	int			x;
	double		texture_position;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistY;
	double		sideDistX;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			lineHeight;
}				t_calc_vars;

typedef struct	s_map_valid {
	int			i;
	int			j;
	int			i1;
	int			j1;
	int			player_flag;
	int			map_i;
}				t_map_valid;

char			**parse_map(char *filename);
void			parse_config_file(char *filename);
void			throw_error(char *error_message);
size_t			count_map_strings(char *str);
void			screenshot();
int				movings(int key);
void			calc();
void			turn_right();
void			scale_reso();
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			create_rgb(int r, int g, int b);
void		draw_celling(int x_view);
void		draw_floor(int x_view);
void		draw_walls(int lineHeight);
void		draw_srpites(double *zBuffer);
void		move_forward(void);
void		move_backward(void);
int		create_rgb(int r, int g, int b);
void	draw_celling(int x_view);
void	draw_floor(int x_view);
void	draw_walls_helper(int y, double step, int color);
void	draw_walls(int line_height);
void	scale_reso();
void	is_screen_size_correct();
void	spawn_direction();
void	data_ini();
void	allocation();
int		mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int		close_window(t_data *data);
void	get_textures();
void	loop_of_mlx(void);
void	prepare_to_draw_helper(void);
int		prepare_to_draw(double *z_buffer, int line_height);
void	throw_error(char *error_message);
int		name_checker(char *name, char *chars);
void	is_resolution_correct(char *line);
void	get_resolution(char *line);
void	to_next_color_char(char *line);
void	check_color_line(char *line);
void	fill_color_in_arr(int *direction, char *line);
void	get_color(int *direction, char *line);
void	copy_north_str(char *line);
void	copy_south_str(char *line);
void	copy_sprite_str(char *line);
void	copy_west_str(char *line);
void	copy_east_str(char *line);
void	sprites_router(char c, char c2, char *line);
void	get_filepath(char *line);
void	is_map_string_valid_helper(const char
								   *line, char *valid_map_chars, int *i, int *j);
void	is_map_string_valid(const char *line);
size_t	count_map_strings(char *str);
void	is_map_valid_helper_2(int **i, int **j, int **i1, int **j1);
void	is_map_valid_helper(int *i, int *j, int *i1, int *j1);
void	map_valid_init(void);
void	is_map_valid_helper_3(void);
int		is_map_valid(void);
void	parse_map_helper(void);

char		**g_map;
char		g_comma;
int			comma_counter;
t_data		*data;
t_texture	*texture;
t_sprites	*sprites;
t_bmp		*bmp;
t_config	*config;
t_calc_vars	*t_calc;
t_sprites	*sprites;
t_texture	*texture_north;
t_texture	*texture_south;
t_texture	*texture_west;
t_texture	*texture_east;
t_texture	*texture_sprite;
t_map_valid	*map_valid;

#endif