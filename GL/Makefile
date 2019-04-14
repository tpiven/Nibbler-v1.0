NAME = gl.dylib

SRC = GL_lib.cpp

FLAGS =  -std=c++11

INC = -I ~/.brew/include -I SOIL/src

LIBS = -L ~/.brew/lib  -lGLEW -lglfw

SOIL = SOIL/lib/libSOIL.a

all: $(NAME)

$(NAME):
	g++ $(FLAGS) -dynamiclib -fPIC -o $(NAME) $(SRC) $(INC) $(LIBS) $(SOIL) -framework OpenGL -framework Appkit

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re: fclean all