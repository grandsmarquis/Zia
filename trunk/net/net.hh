#ifndef	__NET_HH__
#define	__NET_HH__

#ifdef		__linux__
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#elif defined	__FreeBSD__
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#elif defined	_WIN32
#include	<winsock2.h> // <winsock2.h> *MUST* be included before windows.h
#include	<ws2tcpip.h>
#endif 

namespace net
{
  enum AddrFamily{ADDR_LOCAL, ADDR_INET, ADDR_INET6};

  short		netToHostByteOrder(short s);
  short		hostToNetByteOrder(short s);
  int		netToHostByteOrder(int s);
  int		hostToNetByteOrder(int s);
}

#endif
