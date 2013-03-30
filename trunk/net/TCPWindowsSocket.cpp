#include	"TCPWindowsSocket.hh"

namespace      net
{
  namespace    ip
  {
    namespace	tcp
    {
      WindowsSocket::WindowsSocket()
      {
		_sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
      }
      
      WindowsSocket::WindowsSocket(int sock)
      {
		_sock = sock;
      }
      
      WindowsSocket*	WindowsSocket::GetSocketForFd(int socket, struct sockaddr const& addr)
      {
		WindowsSocket*	sock = new WindowsSocket(socket);
		net::EndPoint	remoteEndPoint;
		AWindowsSocket::WindowsAddrToEndPoint(reinterpret_cast<sockaddr_in const&>(addr), remoteEndPoint);
		sock->SetRemoteEndPoint(remoteEndPoint);
		return (sock);
      }
    }
  }
}
