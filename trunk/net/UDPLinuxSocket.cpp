#include	"UDPLinuxSocket.hh"

namespace      net
{
  namespace    ip
  {
    namespace	udp
    {
      LinuxSocket::LinuxSocket()
      {
	_sock = socket(AF_INET, SOCK_DGRAM, 0);
      }
      
      LinuxSocket::LinuxSocket(int sock)
      {
	_sock = sock;
      }
      
      LinuxSocket*	LinuxSocket::GetSocketForFd(int socket, struct sockaddr const& addr)
      {
          LinuxSocket*    sock = new LinuxSocket(socket);
          net::EndPoint   remoteEndPoint;
          AUnixSocket::UnixAddrToEndPoint(reinterpret_cast<sockaddr_in const&>(addr), remoteEndPoint);
          sock->SetRemoteEndPoint(remoteEndPoint);
          return (sock);
      }
    }
  }
}
