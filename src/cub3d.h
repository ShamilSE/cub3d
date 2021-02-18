/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 07:03:13 by mismene           #+#    #+#             */
/*   Updated: 2021/02/18 07:03:16 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include "../headers/mlx.h"
# include "../headers/libft.h"
# include "../headers/ft_printf.h"
# include "../headers/get_next_line.h"
# include <fcntl.h>
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define BUFFER_SIZE 32

typedef struct		s_data
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	void			*mlx;
	void			*win;
	void			*image;
	char			*addr;
	int				bpp;
	int				endian;
	int				size;
	double			move_speed;
	double			rot_speed;
	int				*colours;
	int				i_width;
	int				i_height;
}					t_data;

typedef struct		s_texture
{
	void			*image;
	int				*address;
	int				bpp;
	int				size;
	int				endian;
}					t_texture;

typedef struct		s_sprites
{
	double			*x;
	double			*y;
	int				count;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				stripe;
	int				text_x;
	int				text_y;
	double			dist_tmp;
	double			x_tmp;
	double			y_tmp;
}					t_sprites;

typedef struct		s_bpm
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
}					t_bmp;

typedef struct		s_config {
	char			*filename;
	int				s_width;
	int				s_height;
	char			**map;
	int				floor[4];
	int				celling[4];
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
	char			player;
	unsigned int	map_strings;
}					t_config;

typedef struct		s_calc_vars {
	int				draw_start;
	int				draw_end;
	int				side;
	int				step_x;
	int				step_y;
	int				text_x;
	int				text_y;
	int				x;
	double			texture_position;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_y;
	double			side_dist_x;
	double			delta_dist_y;
	double			delta_dist_x;
	double			perp_wall_dist;
	int				line_height;
}					t_calc_vars;

typedef struct		s_map_valid {
	unsigned int	i;
	unsigned int	j;
	unsigned int	i1;
	unsigned int	j1;
	int				player_flag;
	int				map_i;
}					t_map_valid;

char				**parse_map(char *filename);
void				parse_config_file(char *filename);
void				throw_error(char *error_message);
size_t				count_map_strings(char *str);
void				screenshot();
int					movings(int key);
void				calc();
void				turn_right();
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					create_rgb(int r, int g, int b);
void				draw_celling(int x_view);
void				draw_floor(int x_view);
void				draw_srpites(double *z_buffer);
void				move_forward(void);
void				move_backward(void);
int					create_rgb(int r, int g, int b);
void				draw_celling(int x_view);
void				draw_floor(int x_view);
void				draw_walls_helper(int y, double step, int color);
void				draw_walls(int line_height);
void				scale_reso();
void				is_screen_size_correct();
void				spawn_direction();
void				data_ini();
void				allocation();
int					mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					close_window(t_data *data);
void				get_textures();
void				loop_of_mlx(void);
void				prepare_to_draw_helper(void);
int					prepare_to_draw(double *z_buffer, int line_height);
void				throw_error(char *error_message);
int					name_checker(char *name, char *chars);
void				is_resolution_correct(char *line);
void				get_resolution(char *line);
void				to_next_color_char(char *line);
void				check_color_line(char *line);
void				fill_color_in_arr(int *direction, char *line);
void				get_color(int *direction, char *line);
void				copy_north_str(char *line);
void				copy_south_str(char *line);
void				copy_sprite_str(char *line);
void				copy_west_str(char *line);
void				copy_east_str(char *line);
void				sprites_router(char c, char c2, char *line);
void				get_filepath(char *line);
void				is_map_string_valid_helper(const char
						*line, char *valid_map_chars, int *i, int *j);
void				is_map_string_valid(const char *line);
size_t				count_map_strings(char *str);
void				is_map_valid_helper_2(int **i, int **j, int **i1, int **j1);
void				is_map_valid_helper(int *i, int *j, int *i1, int *j1);
void				map_valid_init(void);
void				is_map_valid_helper_3(void);
int					is_map_valid(void);
void				parse_map_helper(void);
void				count_distance(void);
void				calc_sprites_helper(void);
void				calc_sprites_helper_2(int *d, int *color_sprite, int y);

char				**g_map;
char				g_comma;
int					g_comma_counter;
t_data				*g_data;
t_texture			*g_texture;
t_sprites			*g_sprites;
t_bmp				*g_bmp;
t_config			*g_config;
t_calc_vars			*g_t_calc;
t_sprites			*g_sprites;
t_texture			*g_texture_north;
t_texture			*g_texture_south;
t_texture			*g_texture_west;
t_texture			*g_texture_east;
t_texture			*g_texture_sprite;
t_map_valid			*g_map_valid;

#endif
