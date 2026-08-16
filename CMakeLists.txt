cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(FlappyPigeon VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

if (MSVC)
    add_compile_options(/W4 /WX /permissive- /sdl)
endif()

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(${PROJECT_NAME} WIN32 main.c render.c game_math_priv.c game_math.c sound.c)
add_executable(homework homework.c)
add_subdirectory(game_math)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
)

target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_MAIN_USE_CALLBACKS)

set(FLAPPY_PIGEON_ASSETS
    "background.bmp"
    "Bird.bmp"
    "Bird.png"
    "Bird1.png"
    "column.bmp"
    "column.png"
    "Pixel pigeon.bmp"
    "1-02 - Moon in One's Cup.wav"
    "dragon-studio-dragon-flapping-wings-364476_WIbR3fWD.wav"
    "SDL3.dll"
    "SDL3_image.dll"
)

foreach(asset IN LISTS FLAPPY_PIGEON_ASSETS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/${asset}"
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${asset}"
    )
endforeach()