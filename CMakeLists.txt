cmake_minimum_required(VERSION 3.17)
project(cub3d C)

set(CMAKE_C_STANDARD 99)

add_executable(cub
#        src/main.c
        test_cub/move_player.c
        test_cub/test_cub.c

        src/my_mlx_pixel_put.c
        src/move_player.c
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        config_file_handler/map.cub
        src/draw_map.c
        config_file_handler/parse_map.c
#        src/ray_casting.c
        config_file_handler/parse_config_file.c
#        src/get_texture.c
#        src/main_engine_loop.c
        )
target_link_libraries(cub /Users/shamil/Desktop/CLionProjects/cub3d/libraries/libftprintf.a)
target_link_libraries(cub /Users/shamil/Desktop/CLionProjects/cub3d/libraries/libmlx.a)
target_link_libraries(cub "-framework OpenGL")
target_link_libraries(cub "-framework AppKit")