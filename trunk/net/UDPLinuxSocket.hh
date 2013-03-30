#ifndef	__UDP_LINUX_SOCKET_HH__
#define	__UDP_LINUX_SOCKET_HH__

#include	"AUnixSocket.hh"

namespace      net
{
  namespace    ip
  {
    namespace	udp
    {
      class	LinuxSocket : public AUnixSocket
      {
      public:
	LinuxSocket();
	LinuxSocket(int sock);
    virtual LinuxSocket* GetSocketForFd(int socket, struct sockaddr const& addr);
      };
    }
  }
}

#endif
