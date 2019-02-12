
NAME = libSDL.so

SRC = SDL_lib.cpp TextureManager.cpp

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): 
	g++ $(FLAGS) -shared -fPIC -o $(NAME) $(SRC) -I ~/.brew/include -L ~/.brew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -rpath ~/.brew/lib
	mv $(NAME) ..
	
clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re: fclean all