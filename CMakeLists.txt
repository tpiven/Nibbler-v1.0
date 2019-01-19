cmake_minimum_required(VERSION 3.12)
project(Nibbler_v1.1)

set(CMAKE_CXX_STANDARD 11)
set(SDL2_INCLUDE_DIR ~/.brew/include/SDL2/)
set(SDL2_LIBRARY ~/.brew/lib/)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY})

add_executable(Nibbler_v1.1 main.cpp Game_Obj.cpp Logic.cpp Mmap.cpp AView.cpp SDL_lib.cpp global.h Food.cpp Food.hpp header.h Menu.cpp Menu.hpp)

target_link_libraries(Nibbler_v1.1 -lSDL2 -lSDL2_image)