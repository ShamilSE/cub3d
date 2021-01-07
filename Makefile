NAME = cub3d

MLX_DIR = minilibx_opengl_20191021

MLXFLAGS = -framework OpenGL -framework AppKit

SRC = my_mlx_pixel_put.c main.c

SRC_MLX = $(MLX_DIR)/*.c

MLX_SRC = $(MLX_DIR)/*.c

all: $(NAME)

$(NAME): $(MLX)
	gcc $(SRC) $(MLX_SRC) $(MLX_DIR)/libmlx.a $(MLX_DIR)/mlx.h $(MLXFLAGS) -o $(NAME)

clean:
	rm $(NAME)

re: clean all
