
#ifndef __LISTENER__
#define __LISTENER__

#include <iostream>

#ifdef __unix__
	#include	"UnixThreadSafeSocket.hh"
	#include	"TCPLinuxSocket.hh"
#else
	#include	"WindowsThreadSafeSocket.hh"
	#include	"TCPWindowsSocket.hh"
#endif


class Listener {

public:
  Listener(int port);
  int getPort(void) const;
  net::ISocket *getNewClient(void);
  bool succeedBind() const;

private:
  bool initTCP(int port);

  net::EndPoint _endPoint;
  net::ISocket *_socket;
  int		_port;
  bool		_good;
};

#endif
