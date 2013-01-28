# Tools
RM = rm -rf
MKDIR = mkdir -p

#Directories
SRCDIR = src
INCDIR = inc
OBJDIR = obj

# Files
BIN = event

CXXFILES = src/main.cpp \
					 src/Event/Evented.cpp \
					 src/Event/Callback.cpp

OBJS = $(CXXFILES:.cpp=.o)

# Options
CXXFLAGS = -ggdb
LDFLAGS =

$(BIN): makedirectories $(OBJS)
	$(CXX) -o $(BIN) $(OBJS) $(LDFLAGS)

all: $(BIN)

makedirectories:
	@$(MKDIR) $(OBJDIR)
	@$(MKDIR) $(OBJDIR)/Event

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(BIN)

re: fclean all

.PHONY: re fclean clean
