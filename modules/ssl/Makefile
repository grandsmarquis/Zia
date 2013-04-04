NAME = ssl.so

SRC =	SSLModule.cpp

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -fPIC
LDFLAGS = -shared -fPIC -lboost_filesystem -lboost_filesystem -lpthread

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
