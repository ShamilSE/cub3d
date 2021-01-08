NAME = cub3d

LIBFT = libft.a

MLX = libmlx.a

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(MLX) $(LIBFT) $(NAME)

$(MLX): mlx/*.c
	cd mlx && make && mv $(MLX) ../

$(LIBFT): libft/*.c
	cd libft && make && mv $(LIBFT) ../ && make clean

$(NAME):
	gcc *.c $(LIBFT) libmlx.a $(MLXFLAGS) -o cub3d

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(MLX) $(LIBFT)

re: fclean all
