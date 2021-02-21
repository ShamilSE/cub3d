NAME = cub3D

SRC = src/main.c src/screenshoot.c src/movings.c src/my_mlx_pixel_put.c src/drawing.c src/movings_part_1.c\
    src/drawing_part_1.c src/cub3d_utils.c src/cub3d_utils_part_1.c src/cub3d_utils_part_2.c src/drawing_part_2.c\
	config_file_handler/parse_config_file.c config_file_handler/parse_map.c config_file_handler/parse_config_file_volume_1.c\
	config_file_handler/parse_config_file_volume_2.c config_file_handler/parse_config_file_volume_3.c config_file_handler/parse_map_volume_1.c\
	config_file_handler/parse_map_volume_2.c config_file_handler/parse_config_file_volume_4.c\
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\


OBJ = $(SRC:.c=.o)

MLXFLAGS = -L. -lmlx -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) src/cub3d.h
	make -C mlx
	cp mlx/libmlx.dylib .
	gcc $(CFLAGS) $(SRC) $(MLXFLAGS) libftprintf.a -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf libmlx.dylib
	rm -rf $(NAME)

re: fclean all
