NAME = file.so

SRC =	File.cpp

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -fPIC
LDFLAGS = -shared -fPIC -lboost_system -lboost_filesystem -lboost_locale

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
