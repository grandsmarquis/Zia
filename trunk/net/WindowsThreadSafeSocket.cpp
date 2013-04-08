//
// WindowsThreadSafeSocket.cpp for R-type in /home/petit_v/svn/R-Type/trunk/R-Type/server
// 
// Made by Vianney Petit
// Login   <petit_v@epitech.net>
// 
// Started on  Fri Jan 11 16:07:54 2013 Vianney Petit
// Last update Fri Jan 11 16:14:50 2013 Vianney Petit
//

#include	"WindowsThreadSafeSocket.hh"
#include	<iostream>
namespace net
{
  WindowsThreadSafeSocket::WindowsThreadSafeSocket(net::AWindowsSocket* innerSocket)
    : _innerSocket(innerSocket)
  {
    _mutex.MutexInit();
  }

  WindowsThreadSafeSocket::~WindowsThreadSafeSocket()
  {
    delete _innerSocket;
  }

  ISocket*	WindowsThreadSafeSocket::Accept()
  {
    net::AWindowsSocket*	ret;

    _mutex.MutexLock();
    ret = dynamic_cast<net::AWindowsSocket*>(_innerSocket->Accept());
    _mutex.MutexUnlock();
    if (ret == NULL)
      return (NULL);
    return (new WindowsThreadSafeSocket(ret));
  }

  void	WindowsThreadSafeSocket::EndPointToWindowsAddr(EndPoint const& endPoint, struct sockaddr_in& addr)
  {
    _mutex.MutexLock();
    _innerSocket->EndPointToWindowsAddr(endPoint, addr);
    _mutex.MutexUnlock();
  }
    
    
  void	WindowsThreadSafeSocket::WindowsAddrToEndPoint(struct sockaddr_in const& addr, EndPoint& endPoint)
  {
    _mutex.MutexLock();
    _innerSocket->WindowsAddrToEndPoint(addr, endPoint);
    _mutex.MutexUnlock();
  }

  void	WindowsThreadSafeSocket::Bind(EndPoint& endPoint)
  {
    _mutex.MutexLock();
    _innerSocket->Bind(endPoint);
    _mutex.MutexUnlock();
  }

  void	WindowsThreadSafeSocket::Connect(EndPoint& endPoint)
  {
    _mutex.MutexLock();
    _innerSocket->Connect(endPoint);
    _mutex.MutexUnlock();
  }

  int	WindowsThreadSafeSocket::Recieve(char *buffer, size_t len)
  {
    int	ret;

    _mutex.MutexLock();
    ret = _innerSocket->Recieve(buffer, len);
    _mutex.MutexUnlock();
    return (ret);
  }

  int	WindowsThreadSafeSocket::RecieveFrom(char *buffer, size_t len, net::EndPoint& endPoint)
  {
    int	ret;

    _mutex.MutexLock();
    ret = _innerSocket->RecieveFrom(buffer, len, endPoint);
    _mutex.MutexUnlock();
    return (ret);
  }

  int	WindowsThreadSafeSocket::RecieveAll(char *buffer, size_t len)
  {
    int	ret;

    _mutex.MutexLock();
    ret = _innerSocket->RecieveAll(buffer, len);
    _mutex.MutexUnlock();
    return (ret);
  }

  int	WindowsThreadSafeSocket::Send(char *buffer, size_t len)
  {
    int	ret;

    _mutex.MutexLock();
    ret = _innerSocket->Send(buffer, len);
    _mutex.MutexUnlock();
    return (ret);
  }

  int	WindowsThreadSafeSocket::SendTo(char *buffer, size_t len, EndPoint const& endPoint)
  {
    int	ret;

    _mutex.MutexLock();
    ret = _innerSocket->SendTo(buffer, len, endPoint);
    _mutex.MutexUnlock();
    return (ret);
  }

  int	WindowsThreadSafeSocket::SendAll(char *buffer, size_t len)
  {
    int	ret;

    _mutex.MutexLock();
    ret = _innerSocket->SendAll(buffer, len);
    _mutex.MutexUnlock();
    return (ret);
  }

  bool	WindowsThreadSafeSocket::SetOptions(e_option opt)
  {
    bool	ret;

    _mutex.MutexLock();
    ret = _innerSocket->SetOptions(opt);
    _mutex.MutexUnlock();
    return (ret);
  }

  void	WindowsThreadSafeSocket::Listen()
  {
    _mutex.MutexLock();
    _innerSocket->Listen();
    _mutex.MutexUnlock();
  }

  EndPoint const&	WindowsThreadSafeSocket::GetRemoteEndPoint() const
  {
    _mutex.MutexLock();
    EndPoint const& ret = _innerSocket->GetRemoteEndPoint();
    _mutex.MutexUnlock();
    return (ret);
  }

  int	WindowsThreadSafeSocket::GetSocketRepresentation()
  {
    int		ret;

    _mutex.MutexLock();
    ret = _innerSocket->GetSocketRepresentation();
    _mutex.MutexUnlock();
    return (ret);
  }

  void	WindowsThreadSafeSocket::Close()
  {
    //    _mutex.MutexLock();
    _innerSocket->Close();
    //    _mutex.MutexUnlock();
  }

  void	WindowsThreadSafeSocket::SetRemoteEndPoint(EndPoint const& other)
  {
    _mutex.MutexLock();
    _innerSocket->SetRemoteEndPoint(other);
    _mutex.MutexUnlock();
  }

  net::AWindowsSocket*	WindowsThreadSafeSocket::GetSocketForFd(int socket, struct sockaddr const& addr)
  {
    net::AWindowsSocket*	ret;

    _mutex.MutexLock();
    ret = _innerSocket->GetSocketForFd(socket, addr);
    _mutex.MutexUnlock();      
    return (ret);
  }
}
