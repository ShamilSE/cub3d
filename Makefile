NAME = cub3d

MLX_DIR = minilibx_opengl_20191021

all: $(NAME)

$(NAME):
	gcc *.c libmlx.a -framework OpenGL -framework -AppKit -o cub3d

clean:
	rm $(NAME)

re: clean all
