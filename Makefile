NAME = cub3D

SRC = src/main.c src/screenshoot.c src/movings.c src/my_mlx_pixel_put.c src/drawing.c src/movings_part_1.c\
    src/drawing_part_1.c src/cub3d_utils.c\
	config_file_handler/parse_config_file.c config_file_handler/parse_map.c\
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\

MLXFLAGS = -L. -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

COMPILE_MLX:

$(NAME): $(SRC) src/cub3d.h
	make -C mlx
	cp mlx/libmlx.dylib .
	gcc $(SRC) $(MLXFLAGS) libraries/libftprintf.a -o $(NAME)

clean: fclean
	rm -rf libmlx.dylib
	rm -rf $(NAME)
fclean:
	rm -rf libmlx.dylib
	rm -rf $(NAME)

re: fclean all
