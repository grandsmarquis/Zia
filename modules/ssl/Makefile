NAME = ssl.so

SRC =	SSLModule.cpp

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -fPIC
LDFLAGS = -shared -fPIC -lboost_system -lboost_filesystem -lpthread -lssl

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
