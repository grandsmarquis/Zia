#include	"TCPFreeBSDSocket.hh"

namespace      net
{
  namespace    ip
  {
    namespace	tcp
    {
      FreeBSDSocket::FreeBSDSocket()
      {
	_sock = socket(AF_INET, SOCK_STREAM, 0);
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
