
#ifndef	__ISOCKET_HH__
#define	__ISOCKET_HH__

#include	"EndPoint.hh"

namespace	net
{
  class	ISocket
  {
  public:
    enum e_option{O_NONBLOCKING, O_REUSEADDR};
  public:
    virtual	~ISocket() {};
    virtual ISocket*		Accept() = 0;
    virtual void		Bind(EndPoint& endPoint) = 0;
    virtual void		Close() = 0;
    virtual void		Connect(EndPoint& endPoint) = 0;
    virtual EndPoint const&	GetRemoteEndPoint() const = 0;
    virtual void		Listen() = 0;
    virtual int		Recieve(char *buffer, size_t len) = 0;
    virtual int		RecieveFrom(char *buffer, size_t len, net::EndPoint& endPoint) = 0;
    virtual int		RecieveAll(char *buffer, size_t len) = 0;
    virtual int		Send(char *buffer, size_t len) = 0;
    virtual int		SendTo(char *buffer, size_t len, net::EndPoint const& endPoint) = 0;
    virtual int		SendAll(char *buffer, size_t len) = 0;
    virtual bool	SetOptions(e_option opt) = 0;
    virtual void        SetRemoteEndPoint(EndPoint const& other) = 0;
  };
}

#endif
