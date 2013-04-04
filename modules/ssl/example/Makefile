CXXFLAGS =
LDFLAGS = -lboost_system -lboost_filesystem -lpthread -lssl

all: client.o server.o
	$(CXX) -o client client.o $(LDFLAGS)
	$(CXX) -o server server.o $(LDFLAGS)
