#ifndef	__END_POINT_HH__
#define	__END_POINT_HH__

#include	<string>
#include	<string.h>
#include	"net.hh"

namespace net
{
  class	EndPoint
  {
  private:
    AddrFamily		_addrFamily;
    char		_addrData[8];
    unsigned char	_addrLenght;
    short		_addrPort;
  public:
    EndPoint();
    EndPoint(net::AddrFamily addrFamily, char const* addr, short port);
    short		GetAddrPort() const;
    void		GetAddrData(void* buffer, int* len) const;
    std::string		GetIPStr() const;
    void		SetAddrFamily(net::AddrFamily addrFamily);
    void		SetAddrPort(unsigned short port);
    void		SetAddrData(void const* data, size_t size);
    EndPoint const&	operator=(EndPoint const& other);
  };
}

#include	"ip.hh"

#endif
