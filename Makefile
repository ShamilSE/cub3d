NAME = cub3d

SRC = my_mlx_pixel_put.c my_mlx_line_put.c ft_cast_ray.c events.c main.c draw_square.c

LIBFT = libft.a

MLX = libmlx.a

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(MLX) $(LIBFT) $(NAME)

$(MLX): mlx/*.c
	cd mlx && make && mv $(MLX) ../

$(LIBFT): libft/*.c
	cd libft && make && mv $(LIBFT) ../ && make clean

$(NAME): $(SRC)
	gcc $(SRC) $(LIBFT) libmlx.a $(MLXFLAGS) -o cub3d

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(MLX) $(LIBFT)

re: fclean all
