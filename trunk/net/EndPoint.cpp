#include	"EndPoint.hh"

namespace net
{
  EndPoint::EndPoint()
  {
  }

  EndPoint::EndPoint(net::AddrFamily addrFamily, char const* addr, short addrPort)
    : _addrFamily(addrFamily), _addrPort(net::hostToNetByteOrder(addrPort))
  {
    if (_addrFamily == net::ADDR_INET)
      {
	if (addr != NULL)
	  {
	    try {
	      ip::packIP(addr, _addrData);
	    } catch (std::exception const& e) {
	      int	tmp = INADDR_ANY;
	      memcpy(_addrData, &tmp, sizeof(INADDR_ANY));
	    }
	  }
	else
	  {
	    int	tmp = INADDR_ANY;
	    memcpy(_addrData, &tmp, sizeof(INADDR_ANY));
	  }
	_addrLenght = 8;
      }
    else if (_addrFamily == net::ADDR_INET6)
      {
	if (addr != NULL)
	  ip6::packIP(addr, _addrData);
	else
	  memcpy(_addrData, &in6addr_any, sizeof(sizeof(INADDR_ANY)));
	_addrLenght = 8; // Not sure, inet_ntop fills only 14 bytes
	// TODO: maybe pack should return the lenght
      }
  }

  short	EndPoint::GetAddrPort() const
  {
    return (_addrPort);
  }

  void	EndPoint::GetAddrData(void* buffer, int* len) const
  {
    memcpy(buffer, _addrData, _addrLenght);
    *len = _addrLenght;
  }

  std::string	EndPoint::GetIPStr() const
  {
    char	ip[32];

    net::ip::unpackIP(_addrData, ip, sizeof(ip));
    return (std::string(ip));
  }

  EndPoint const&	EndPoint::operator=(EndPoint const& other)
  {
    _addrFamily = other._addrFamily;
    memcpy(_addrData, other._addrData, other._addrLenght);
    _addrLenght = other._addrLenght;
    _addrPort = other._addrPort;
    return (*this);
  }

  void	EndPoint::SetAddrFamily(net::AddrFamily addrFamily)
  {
    _addrFamily = addrFamily;
  }

  void	EndPoint::SetAddrPort(unsigned short port)
  {
    _addrPort = port;
  }

  void	EndPoint::SetAddrData(void const* data, size_t size)
  {
    memcpy(_addrData, data, size);
    _addrLenght = size;
  }
}
