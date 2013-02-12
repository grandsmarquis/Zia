# Tools
RM = rm -rf
MKDIR = mkdir -p

# Files
BIN = server

CXXFILES = Zia/main.cpp \
					 Zia/event/Callback.cpp \
					 Zia/net/Exception.cpp \
					 Zia/net/Socket.cpp \
					 Zia/net/TCPSocket.cpp \
					 Zia/thread/Cond.cpp \
					 Zia/thread/Exception.cpp \
					 Zia/thread/Mutex.cpp \
					 Zia/thread/Thread.cpp

OBJS = $(CXXFILES:.cpp=.o)

# Options
CXXFLAGS = -ggdb
LDFLAGS = -lpthread

$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $(OBJS) $(LDFLAGS)

all: $(BIN)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(BIN)

re: fclean all

.PHONY: re fclean clean
