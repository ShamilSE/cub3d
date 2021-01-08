cmake_minimum_required(VERSION 3.17)
project(cub3d C)

set(CMAKE_C_STANDARD 99)

add_executable(cub main.c my_mlx_pixel_put.c my_mlx_line_put.c ft_cast_ray.c hooks.c)
target_link_libraries(cub /Users/mismene/Desktop/CLionProjects/cub3d/libft.a)
target_link_libraries(cub /Users/mismene/Desktop/CLionProjects/cub3d/libmlx.a)
target_link_libraries(cub "-framework OpenGL")
target_link_libraries(cub "-framework AppKit")