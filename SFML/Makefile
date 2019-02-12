
NAME = libSFML.so

SRC = SFML_lib.cpp

FLAGS = -Wall -Wextra -Werror -std=c++11

all: $(NAME)

$(NAME): 
	g++ $(FLAGS) -shared -fPIC -o $(NAME) $(SRC) -I ~/.brew/include -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -rpath ~/.brew/lib
	mv $(NAME) ..
	
clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re: fclean all