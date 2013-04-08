
NAME=		Zia

SRC= 		main.cpp			\
		Listener.cpp			\
		Daemon.cpp			\
		DaemonManager.cpp		\
		Bucket.cpp			\
		HTTPParser.cpp			\
		mutex/MutexCross.cpp		\
		mutex/MutexUnix.cpp		\
		net/EndPoint.cpp		\
		net/net.cpp			\
		net/ip.cpp			\
		net/Selector.cpp		\
		net/AUnixSocket.cpp		\
		net/TCPLinuxSocket.cpp		\
		net/UDPLinuxSocket.cpp		\
		net/UnixThreadSafeSocket.cpp	\
		thread/ThreadUnix.cpp		\
		thread/TLSUnix.cpp		\
		apisources/Body.cpp		\
		apisources/Response.cpp		\
		apisources/ResponseHeader.cpp	\
		apisources/Request.cpp		\
		apisources/RequestHeader.cpp	\
		SoObjectFactory.cpp		\
		ConfigManager.cpp


OBJ=		$(SRC:.cpp=.o)

CC=		g++ -g

RM=		rm -rf

INCLUDES=	-I ./mutex/			\
		-I  ./net/			\
		-I  ./apiheaders		\
		-I  ./thread/

CPPFLAGS=	-g -W -Wall -Wextra $(INCLUDES)

LIBS=		-lpthread -ldl -lconfig++

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -rdynamic $(OBJ) -o $(NAME) $(LIBS)

clean:
		$(RM) $(OBJ)

fclean:
		$(RM) $(OBJ) $(NAME)

re:		fclean all
