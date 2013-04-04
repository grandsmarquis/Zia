NAME = php.so

SRC =	PHPModule.cpp

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -fPIC
LDFLAGS = -shared -fPIC

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
