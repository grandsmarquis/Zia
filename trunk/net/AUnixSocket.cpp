#include	"AUnixSocket.hh"

// TODO: debug
#include	<cstdio>
#include	<iostream>

namespace      net
{
  AUnixSocket::AUnixSocket()
  {
    _sock = -1;
  }

  AUnixSocket::~AUnixSocket()
  {
  }

  ISocket*	AUnixSocket::Accept()
  {
    struct sockaddr	addr;
    socklen_t		addr_len;
    int			client_sock;

    // TODO : crete ISocket and set sock remote endpoint
    addr_len = sizeof(addr);
    if ((client_sock = accept(_sock, &addr, &addr_len)) == -1)
      {
	//throw;
	//perror("Accept():");
	return (NULL);
      }
    return (GetSocketForFd(client_sock, addr));
  }

  void	AUnixSocket::EndPointToUnixAddr(EndPoint const& endPoint, struct sockaddr_in& addr)
  {
    int			addrLen;

    addr.sin_family = AF_INET;
    addr.sin_port = endPoint.GetAddrPort();
    endPoint.GetAddrData(&addr.sin_addr, &addrLen);
  }


  void	AUnixSocket::UnixAddrToEndPoint(struct sockaddr_in const& addr, EndPoint& endPoint)
  {
    endPoint.SetAddrFamily(net::ADDR_INET);
    endPoint.SetAddrPort(addr.sin_port);
    endPoint.SetAddrData(reinterpret_cast<void const*>(&addr.sin_addr), sizeof(addr.sin_addr));
  }

  void	AUnixSocket::Bind(EndPoint& endPoint)
  {
    struct sockaddr_in	addr;

    EndPointToUnixAddr(endPoint, addr);
    if (bind(_sock, (sockaddr*)&addr, sizeof(struct sockaddr)) == -1)
      throw std::exception();
    _remoteEndPoint = endPoint; // new
  }

  void	AUnixSocket::Connect(EndPoint& endPoint)
  {
    struct sockaddr_in	addr;

    EndPointToUnixAddr(endPoint, addr);
    if (connect(_sock, (sockaddr*)&addr, sizeof(struct sockaddr)) == -1)
      throw std::exception();
    _remoteEndPoint = endPoint;
  }

  int	AUnixSocket::Recieve(char *buffer, size_t len)
  {
    return (recv(_sock, buffer, len, 0));
  }

  int	AUnixSocket::RecieveFrom(char *buffer, size_t len, net::EndPoint& endPoint)
  {
    struct sockaddr_in	addr;
    socklen_t		addrLen = sizeof(struct sockaddr);
    int			ret;

    ret = recvfrom(_sock, buffer, len, 0, (struct sockaddr*)&addr, &addrLen);
    if (ret >= 0)
      UnixAddrToEndPoint(addr, endPoint);
    return (ret);
  }

  int	AUnixSocket::RecieveAll(char *buffer, size_t len)
  {
    (void) buffer;
    (void) len;
    return (-1);
  }

  int	AUnixSocket::Send(char *buffer, size_t len)
  {
    return (send(_sock, buffer, len, MSG_NOSIGNAL));
  }

  int	AUnixSocket::SendTo(char *buffer, size_t len, EndPoint const& endPoint)
  {
    struct sockaddr_in	addr;
    socklen_t		addrLen = sizeof(struct sockaddr);
    int			ret;

    EndPointToUnixAddr(endPoint, addr);
    ret = sendto(_sock, buffer, len, MSG_NOSIGNAL, (struct sockaddr*)&addr, addrLen);
    return (ret);
  }

  int	AUnixSocket::SendAll(char *buffer, size_t len)
  {
    int		sentBytes = 0;
    int		ret;

    while (static_cast<size_t>(sentBytes) < len)
      {
	ret = Send(buffer + sentBytes, len - sentBytes);
	if (ret > 0)
	  sentBytes += ret;
	else if (errno != EAGAIN && errno != EWOULDBLOCK)
	  return (ret);
      }
    return (sentBytes);
  }

  bool	AUnixSocket::SetOptions(e_option opt)
  {
    if (opt == net::ISocket::O_NONBLOCKING)
      fcntl(_sock, F_SETFL, O_NONBLOCK);
    else if (opt == net::ISocket::O_REUSEADDR)
      {
	int	reuse = 1;
	setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, (int *)&reuse, sizeof(reuse));
      }
    return (true);
  }

  void	AUnixSocket::Listen()
  {
    if (listen(_sock, 0))
      throw std::exception();
  }

  EndPoint const&	AUnixSocket::GetRemoteEndPoint() const
  {
    return (_remoteEndPoint);
  }

  int	AUnixSocket::GetSocketRepresentation()
  {
    return (_sock);
  }

  void	AUnixSocket::Close()
  {
    close(_sock);
    _sock = -1;
  }

  void	AUnixSocket::SetRemoteEndPoint(EndPoint const& other)
  {
    _remoteEndPoint = other;
  }
}
