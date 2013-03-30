//
// UnixThreadSafeSocket.cpp for R-type in /home/petit_v/svn/R-Type/trunk/R-Type/server
// 
// Made by Vianney Petit
// Login   <petit_v@epitech.net>
// 
// Started on  Fri Jan 11 16:07:54 2013 Vianney Petit
// Last update Fri Jan 11 16:14:50 2013 Vianney Petit
//

#include	"UnixThreadSafeSocket.hh"
#include	<iostream>
namespace net
{
  UnixThreadSafeSocket::UnixThreadSafeSocket(net::AUnixSocket* innerSocket)
    : _innerSocket(innerSocket)
  {
    _mutex.MutexInit();
  }

  UnixThreadSafeSocket::~UnixThreadSafeSocket()
  {
    delete _innerSocket;
  }

  ISocket*	UnixThreadSafeSocket::Accept()
  {
    net::AUnixSocket*	ret;

    _mutex.MutexLock();
    ret = dynamic_cast<net::AUnixSocket*>(_innerSocket->Accept());
    _mutex.MutexUnlock();
    if (ret == NULL)
      return (NULL);
    return (new UnixThreadSafeSocket(ret));
  }

  void	UnixThreadSafeSocket::EndPointToUnixAddr(EndPoint const& endPoint, struct sockaddr_in& addr)
  {
    _mutex.MutexLock();
    _innerSocket->EndPointToUnixAddr(endPoint, addr);
    _mutex.MutexUnlock();
  }
    
    
  void	UnixThreadSafeSocket::UnixAddrToEndPoint(struct sockaddr_in const& addr, EndPoint& endPoint)
  {
    _mutex.MutexLock();
    _innerSocket->UnixAddrToEndPoint(addr, endPoint);
    _mutex.MutexUnlock();
  }

  void	UnixThreadSafeSocket::Bind(EndPoint& endPoint)
  {
    _mutex.MutexLock();
    _innerSocket->Bind(endPoint);
    _mutex.MutexUnlock();
  }

  void	UnixThreadSafeSocket::Connect(EndPoint& endPoint)
  {
    _mutex.MutexLock();
    _innerSocket->Connect(endPoint);
    _mutex.MutexUnlock();
  }

  int	UnixThreadSafeSocket::Recieve(char *buffer, size_t len)
  {
    int	ret;

    _mutex.MutexLock();
    ret = _innerSocket->Recieve(buffer, len);
    _mutex.MutexUnlock();
    return (ret);
  }

  int	UnixThreadSafeSocket::RecieveFrom(char *buffer, size_t len, net::EndPoint& endPoint)
  {
    int	ret;

    _mutex.MutexLock();
    ret = _innerSocket->RecieveFrom(buffer, len, endPoint);
    _mutex.MutexUnlock();
    return (ret);
  }

  int	UnixThreadSafeSocket::RecieveAll(char *buffer, size_t len)
  {
    int	ret;

    _mutex.MutexLock();
    ret = _innerSocket->RecieveAll(buffer, len);
    _mutex.MutexUnlock();
    return (ret);
  }

  int	UnixThreadSafeSocket::Send(char *buffer, size_t len)
  {
    int	ret;

    _mutex.MutexLock();
    ret = _innerSocket->Send(buffer, len);
    _mutex.MutexUnlock();
    return (ret);
  }

  int	UnixThreadSafeSocket::SendTo(char *buffer, size_t len, EndPoint const& endPoint)
  {
    int	ret;

    _mutex.MutexLock();
    ret = _innerSocket->SendTo(buffer, len, endPoint);
    _mutex.MutexUnlock();
    return (ret);
  }

  int	UnixThreadSafeSocket::SendAll(char *buffer, size_t len)
  {
    int	ret;

    _mutex.MutexLock();
    ret = _innerSocket->SendAll(buffer, len);
    _mutex.MutexUnlock();
    return (ret);
  }

  bool	UnixThreadSafeSocket::SetOptions(e_option opt)
  {
    bool	ret;

    _mutex.MutexLock();
    ret = _innerSocket->SetOptions(opt);
    _mutex.MutexUnlock();
    return (ret);
  }

  void	UnixThreadSafeSocket::Listen()
  {
    _mutex.MutexLock();
    _innerSocket->Listen();
    _mutex.MutexUnlock();
  }

  EndPoint const&	UnixThreadSafeSocket::GetRemoteEndPoint() const
  {
    _mutex.MutexLock();
    EndPoint const& ret = _innerSocket->GetRemoteEndPoint();
    _mutex.MutexUnlock();
    return (ret);
  }

  int	UnixThreadSafeSocket::GetSocketRepresentation()
  {
    int		ret;

    _mutex.MutexLock();
    ret = _innerSocket->GetSocketRepresentation();
    _mutex.MutexUnlock();
    return (ret);
  }

  void	UnixThreadSafeSocket::Close()
  {
    _mutex.MutexLock();
    _innerSocket->Close();
    _mutex.MutexUnlock();
  }

  void	UnixThreadSafeSocket::SetRemoteEndPoint(EndPoint const& other)
  {
    _mutex.MutexLock();
    _innerSocket->SetRemoteEndPoint(other);
    _mutex.MutexUnlock();
  }

  net::AUnixSocket*	UnixThreadSafeSocket::GetSocketForFd(int socket, struct sockaddr const& addr)
  {
    net::AUnixSocket*	ret;

    _mutex.MutexLock();
    ret = _innerSocket->GetSocketForFd(socket, addr);
    _mutex.MutexUnlock();      
    return (ret);
  }
}
