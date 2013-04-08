NAME = php.so

SRC =	PHPModule.cpp

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -W -Wall -fPIC -I ../trunk -I ../trunk/apiheaders
LDFLAGS = -shared -fPIC -lboost_system -lboost_filesystem

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
