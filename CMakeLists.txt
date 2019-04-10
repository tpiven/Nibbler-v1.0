cmake_minimum_required(VERSION 3.12)
project(Nibbler_v1.1)

add_custom_target(SDL_lib
                  COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/SDL)
add_custom_target(SFML_lib
                  COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/SFML)

add_custom_target(Allegro_lib
        COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/Allegro)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Menu.cpp Game_Obj.cpp Logic.cpp Mmap.cpp
                 AView.cpp Food.cpp Interface.cpp Interface.hpp GL/GL_lib.cpp)

message(STATUS "dir = '${CMAKE_CURRENT_SOURCE_DIR}'")

if (linux)
    set(INCLUDE_DIR /usr/include/GLFW)
    set(SOIL_INCLUDE_DIR  /home/kmykhailenko/Unit/GLFW/SOIL/src)

    set(LIB /usr/lib)
    set(SOIL_LIB /home/kmykhailenko/Unit/GLFW/SOIL/lib)

    include_directories(${INCLUDE_DIR})
    link_directories(${LIB})

    include_directories(SOIL_LIB /home/kmykhailenko/Unit/GLFW/SOIL/lib)
    link_directories(${SOIL_LIB})

    message("UNIX!")


    include_directories(H_SOIL /home/kmykhailenko/Unit/GLFW/SOIL/src)
    link_directories(${H_SOIL})

endif()

if (APPLE)
    set(INCLUDE_DIR ~/.brew/include/)
#    set(SOIL_INCLUDE_DIR  /Users/kmykhail/OPENGL/OPEN/SOIL/src)
    set(SOIL_INCLUDE_DIR GL/SOIL/src)
    set(LIB  ~/.brew/lib/)
#    set(SOIL_LIB /Users/kmykhail/OPENGL/OPEN/SOIL/lib)
    set(SOIL_LIB GL/SOIL/lib)

    include_directories(${INCLUDE_DIR})
    link_directories(${LIB})


#    include_directories(SOIL_LIB /Users/kmykhail/OPENGL/OPEN/SOIL/lib)
    include_directories(SOIL_LIB GL/SOIL/lib)
    link_directories(${SOIL_LIB})

#    include_directories(H_SOIL /Users/kmykhail/OPENGL/OPEN/SOIL/src)
    include_directories(H_SOIL GL/SOIL/src)
    link_directories(${H_SOIL})

    set(CMAKE_CXX_STANDARD 11)
    set(SDL2_INCLUDE_DIR ~/.brew/include/SDL2/)
    set(SDL2_LIBRARY ~/.brew/lib/)
    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIBRARY})

    message("!!APPLE")

endif(APPLE)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(Nibbler_v1.1 ${SOURCE_FILES})

#target_link_libraries(Nibbler_v1.1 -rdynamic -ldl)
target_link_libraries(Nibbler_v1.1 ${CMAKE_BINARY_DIR}/../GL/SOIL/lib/libSOIL.a ${OPENGL_LIBRARY} ${GLUT_LIBRARY} -lGLEW -lglfw -lSDL2 -lSDL2_image -lSDL2_ttf)