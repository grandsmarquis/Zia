#ifndef		__IP_HH__
#define		__IP_HH__

#include	"net.hh"
#include	"EndPoint.hh"

namespace	net
{
  namespace	ip
  {
    void		packIP(char const* src, void* dst);
    void		unpackIP(void const* src, char* dst, size_t size);
    EndPoint		GetAnyIPEndPoint(short port);
    EndPoint		GetIPEndPoint(char const* ip, short port);
  }

  namespace	ip6
  {
    void		packIP(char const* src, void* dst);
    void		unpackIP(void const* src, char* dst, size_t size);
    EndPoint		GetAnyIPEndPoint(short port);
    EndPoint		GetIPEndPoint(char const* ip, short port);
  }
}

#endif
