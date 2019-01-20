cmake_minimum_required(VERSION 3.12)
project(Nibbler_v1.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Menu.cpp Game_Obj.cpp Logic.cpp Mmap.cpp AView.cpp Food.cpp SFML_lib.cpp SDL_lib.cpp)
set(INCLUDE_DIR ~/.brew/include/)
set(LIBRARY ~/.brew/lib/)

include_directories(${INCLUDE_DIR})
link_directories(${LIBRARY})

add_executable(Nibbler_v1.1 ${SOURCE_FILES})
target_link_libraries(Nibbler_v1.1  -lSDL2 -lSDL2_image -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -lsfml-system)

