
NAME = libAllegro.so

SRC =  Allegra_lib.cpp 

FLAGS = -Wall -Wextra -Werror -std=c++11

all: $(NAME)

$(NAME): 
	g++ $(FLAGS) -shared -fPIC -o $(NAME) $(SRC) -I ~/.brew/include -L ~/.brew/lib -lallegro -lallegro_image  -rpath ~/.brew/lib
	mv $(NAME) ..
	
clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re: fclean all