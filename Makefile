NAME = cub3d

SRC = my_mlx_pixel_put.c my_mlx_line_put.c main.c get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c move_player.c draw_map.c config_file_handler/parse_map.c throw_ray.c\
	config_file_handler/parse_config_file.c get_texture.c

MLXFLAGS = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(SRC)
	gcc $(SRC) libraries/libftprintf.a libraries/libmlx.a $(MLXFLAGS) -o cub3d

clean:
	@rm -rf $(NAME)

fclean: clean
	@rm -rf $(MLX) $(LIBFT)

re: fclean all
