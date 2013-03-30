#ifndef	__TCP_FREEBSD_SOCKET_HH__
#define	__TCP_FREEBSD_SOCKET_HH__

#include	"AUnixSocket.hh"

namespace      net
{
  namespace    ip
  {
    namespace	tcp
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
