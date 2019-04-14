NAME = gl.dylib

SRC = GL_lib.cpp

FLAGS = -Wall -Wextra -Werror -std=c++11

INC = -I ~/.brew/include SOIL/src

LIBS = -L ~/.brew/lib  -lGLEW -lglfw SOIL/lib/libSOIL.a 

all: $(NAME)

$(NAME):
	g++ $(FLAGS) -dynamiclib -fPIC -o $(NAME) $(SRC) $(INC) $(LIBS) -framework OpenGL

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re: fclean all