cmake_minimum_required(VERSION 3.17)
project(cub3d C)

set(CMAKE_C_STANDARD 99)

add_executable(cub main.c my_mlx_pixel_put.c my_mlx_line_put.c move_player.c get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c map.cub draw_map.c parse_map.c throw_ray.c)
target_link_libraries(cub /Users/mismene/Desktop/CLionProjects/cub3d/libraries/libftprintf.a)
target_link_libraries(cub /Users/mismene/Desktop/CLionProjects/cub3d/libraries/libmlx.a)
target_link_libraries(cub "-framework OpenGL")
target_link_libraries(cub "-framework AppKit")