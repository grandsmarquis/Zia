//
// AUnixSocket.hh for babel in /home/petit_v/svn/babel-2015-demouc_m/trunk/common/src
// 
// Made by Vianney Petit
// Login   <petit_v@epitech.net>
// 
// Started on  Fri Nov 23 07:42:27 2012 Vianney Petit
// Last update Fri Jan 11 16:04:07 2013 Vianney Petit
//

#ifndef	__AUNIX_SOCKET_HH__
#define	__AUNIX_SOCKET_HH__

#include	<cstring>
#include	<fcntl.h>
#ifdef __unix__
#include	<unistd.h>
#include	<errno.h>
#endif
#include	"ISocket.hh"

namespace      net
{
  class	AUnixSocket : public ISocket
  {
  protected:
    int	_sock;
    EndPoint	_remoteEndPoint;
  public:
    void	EndPointToUnixAddr(EndPoint const& endPoint, struct sockaddr_in& addr);
    void	UnixAddrToEndPoint(struct sockaddr_in const& addr, EndPoint& endPoint);
  public:
    virtual ~AUnixSocket();
    AUnixSocket();
    virtual ISocket*		Accept();
    virtual void		Bind(EndPoint& endPoint);
    virtual void		Close();
    virtual void		Connect(EndPoint& endPoint);
    //Diconnect();
    //GetAvailableBytes();
    //GetOptions();
    virtual EndPoint const&   GetRemoteEndPoint() const;
    virtual void		Listen();
    virtual int		Recieve(char *buffer, size_t len);
    virtual int		RecieveFrom(char *buffer, size_t len, EndPoint& endPoint);
    virtual int		RecieveAll(char *buffer, size_t len);
    virtual int		Send(char *buffer, size_t len);
    virtual int		SendTo(char *buffer, size_t len, EndPoint const& endPoint);
    virtual int		SendAll(char *buffer, size_t len);
    virtual bool        SetOptions(e_option opt);
    virtual void	SetRemoteEndPoint(EndPoint const& other);

    /* ??? */
    virtual AUnixSocket*	GetSocketForFd(int fd, struct sockaddr const& addr) = 0;
    virtual int			GetSocketRepresentation();
  };
}

#endif
