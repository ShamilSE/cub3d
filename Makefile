NAME = cub3d

SRC = my_mlx_pixel_put.c my_mlx_line_put.c ft_cast_ray.c events.c main.c draw_square.c

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(SRC)
	gcc $(SRC) libraries/libmlx.a libraries/libftprintf.a $(MLXFLAGS) -o cub3d

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(MLX) $(LIBFT)

re: fclean all
