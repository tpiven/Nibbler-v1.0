cmake_minimum_required(VERSION 3.12)
project(Nibbler_v1.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_custom_command(OUTPUT SDL/Makefile
        COMMAND make run
        WORKING_DIRECTORY SDL)


set(SOURCE_FILES main.cpp Menu.cpp Game_Obj.cpp Logic.cpp Mmap.cpp AView.cpp Food.cpp Interface.cpp Interface.hpp)
set(INCLUDE_DIR ~/.brew/include/)
set(LIBRARY ~/.brew/lib/)
include_directories(${INCLUDE_DIR})
link_directories(${LIBRARY})

#set(CMAKE_CXX_CREATE_SHARED_LIBRARY -dynamiclib -fPIC -lSDL2 -lSDL2_image -lSDL2_ttf)
#add_library(libSDL SHARED SDL/SDL_lib.cpp SDL/TextureManager.cpp)

#set(SDL_SOURCES SDL/SDL_lib.cpp SDL/TextureManager.cpp)
#add_executable(libSDL.dylib ${SDL_SOURCES})
#target_link_libraries(libSDL.dylib -dynamiclib -fPIC -lSDL2 -lSDL2_image -lSDL2_ttf)


add_executable(Nibbler_v1.1 ${SOURCE_FILES})

target_link_libraries(Nibbler_v1.1 -rdynamic -ldl)
