#ifndef	__UDP_LINUX_SOCKET_HH__
#define	__UDP_LINUX_SOCKET_HH__

#include	"AUnixSocket.hh"

namespace      net
{
  namespace    ip
  {
    namespace	udp
    {
      class	FreeBSDSocket : public AUnixSocket
      {
      public:
	FreeBSDSocket();
	FreeBSDSocket(int sock);
	virtual FreeBSDSocket* GetSocketForFd(int socket);
      };
    }
  }
}

#endif
