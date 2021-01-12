NAME = cub3d

SRC = my_mlx_pixel_put.c my_mlx_line_put.c ft_cast_ray.c main.c get_next_line.c get_next_line_utils.c

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(SRC)
	gcc $(SRC) libraries/libmlx.a libraries/libftprintf.a $(MLXFLAGS) -o cub3d

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(MLX) $(LIBFT)

re: fclean all
