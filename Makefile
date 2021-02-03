NAME = cub3d

SRC = test_cub/test_cub.c

MLXFLAGS = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(SRC)
	gcc $(SRC) libraries/libftprintf.a libraries/libmlx.a $(MLXFLAGS) -o cub3d

clean:
	@rm -rf $(NAME)

fclean: clean
	@rm -rf $(MLX) $(LIBFT)

re: fclean all
