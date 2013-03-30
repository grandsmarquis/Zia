#ifndef	__UDP_WINDOWS_SOCKET_HH__
#define	__UDP_WINDOWS_SOCKET_HH__

#include	"AWindowsSocket.hh"

namespace      net
{
  namespace    ip
  {
    namespace	udp
    {
      class	WindowsSocket : public AWindowsSocket
      {
      public:
		WindowsSocket();
		WindowsSocket(int sock);
		virtual WindowsSocket* GetSocketForFd(int socket, struct sockaddr const& addr);
      };
    }
  }
}

#endif
