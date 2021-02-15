NAME = cub3D

SRC = src/main.c src/screenshoot.c src/movings.c src/my_mlx_pixel_put.c src/drawing.c\
	config_file_handler/parse_config_file.c config_file_handler/parse_map.c\
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\

MLXFLAGS = -L. -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

COMPILE_MLX:

$(NAME): $(SRC)
	make -C mlx
	cp mlx/libmlx.dylib .
	gcc $(SRC) $(MLXFLAGS) libraries/libftprintf.a -o $(NAME)

clean:
	rm -rf libmlx.dylib
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAME)

re: fclean all
