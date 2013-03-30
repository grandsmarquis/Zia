#include	"UDPFreeBSDSocket.hh"

namespace      net
{
  namespace    ip
  {
    namespace	udp
    {
      FreeBSDSocket::FreeBSDSocket()
      {
	_sock = socket(AF_INET, SOCK_DGRAM, 0);
      }
      
      FreeBSDSocket::FreeBSDSocket(int sock)
      {
	_sock = sock;
      }
      
      FreeBSDSocket*	FreeBSDSocket::GetSocketForFd(int socket)
      {
	return (new FreeBSDSocket(socket));
      }
    }
  }
}
