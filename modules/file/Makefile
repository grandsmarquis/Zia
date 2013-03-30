NAME = file.so

SRC =	File.cpp

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -fPIC
LDFLAGS = -shared -fPIC

$(NAME): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
