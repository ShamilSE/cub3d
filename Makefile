NAME = cub3d

MLX_DIR = minilibx_opengl_20191021

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

LIBFT_DIR = libft

all: $(NAME)

$(NAME):
	gcc *.c -L $(LIBFT_DIR) -lft libmlx.a $(MLXFLAGS) -o cub3d

clean:
	rm $(NAME)

re: clean all
