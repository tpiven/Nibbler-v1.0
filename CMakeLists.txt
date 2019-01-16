cmake_minimum_required(VERSION 3.12)
project(Nibbler_v1.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSFML_STATIC")
add_executable(Nibbler_v1.1 main.cpp Game_Obj.cpp Logic.cpp Mmap.cpp AView.cpp global.h Food.cpp Food.hpp header.h SFML_lib.cpp SFML_lib.hpp)

target_link_libraries(Nibbler_v1.1 -lsfml-window-s -lgdi32 -lsfml-graphics-s -lopengl32 -lfreetype -lsfml-audio-s -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lsfml-network-s -lsfml-system-s -lwinmm -lz)



