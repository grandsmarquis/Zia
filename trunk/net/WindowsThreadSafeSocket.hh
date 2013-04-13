//
// WindowsThreadSafeSocket.hh for babel in /home/petit_v/svn/babel-2015-demouc_m/trunk/common/src
// 
// Made by Vianney Petit
// Login   <petit_v@epitech.net>
// 
// Started on  Fri Nov 23 07:42:27 2012 Vianney Petit
// Last update Fri Jan 11 16:11:00 2013 Vianney Petit
//

#ifndef	__WINDOWS_THREAD_SAFE_SOCKET_HH__
#define	__WINDOWS_THREAD_SAFE_SOCKET_HH__

#include	"AWindowsSocket.hh"
#include	"MutexCSWindows.hpp"

namespace      net
{
  class	WindowsThreadSafeSocket : public AWindowsSocket
  {
  private:
    net::AWindowsSocket*	_innerSocket;
    mutable MutexCSWindows	_mutex;
  public:
    WindowsThreadSafeSocket(net::AWindowsSocket* innerSocket);
    virtual ~WindowsThreadSafeSocket();
    ISocket*	Accept();
    void	EndPointToWindowsAddr(EndPoint const& endPoint, struct sockaddr_in& addr);
    void	WindowsAddrToEndPoint(struct sockaddr_in const& addr, EndPoint& endPoint);
    void	Bind(EndPoint& endPoint);
    void	Connect(EndPoint& endPoint);
    int	Recieve(char *buffer, size_t len);
    int	RecieveFrom(char *buffer, size_t len, net::EndPoint& endPoint);
    int	RecieveAll(char *buffer, size_t len);
    int	Send(char *buffer, size_t len);
    int	SendTo(char *buffer, size_t len, EndPoint const& endPoint);
    int	SendAll(char *buffer, size_t len);
    bool	SetOptions(e_option opt);
    void	Listen();
    EndPoint const&	GetRemoteEndPoint() const;
    int	GetSocketRepresentation();
    void	Close();
    void	SetRemoteEndPoint(EndPoint const& other);
    net::AWindowsSocket*	GetSocketForFd(int socket, struct sockaddr const& addr);
	virtual int getFD() const
	{
		return (_innerSocket->getFD());
	}
  };
}

#endif
