#include	"ip.hh"
#include	<cstdio>

namespace	net
{
  namespace	ip
  {
    void	packIP(char const* src, void* dst)
    {
#ifdef __unix__
      if (inet_pton(AF_INET, src, dst) <= 0)
	{
	  printf("inet_pton failed\n");
	  throw std::exception();
	}
#elif defined _WIN32
      int			len;
      SOCKADDR			addr;

      len = sizeof(SOCKADDR);
      if (WSAStringToAddress(const_cast<char*>(src), AF_INET, NULL, &addr, &len) == SOCKET_ERROR) {
	printf("pack ip wsa strig to address%d\n", WSAGetLastError());
	throw std::exception();
      }
      LPSOCKADDR_IN a = reinterpret_cast<LPSOCKADDR_IN>(&addr);
      memcpy(dst, &a->sin_addr, 8);
#endif
    }

    void	unpackIP(void const* src, char* dst, size_t size)
    {
#ifdef __unix__
      if (inet_ntop(AF_INET, src, dst, size) == NULL)
	printf("inet_ntop failed\n");
#elif defined _WIN32
      SOCKADDR_IN	addr;
      addr.sin_family = AF_INET;
      addr.sin_port = 0;
      memcpy(&addr.sin_addr, src, 8); // TODO : 8 ????
      if (WSAAddressToString((LPSOCKADDR)&addr, sizeof(SOCKADDR), NULL, dst, (LPDWORD)&size) == SOCKET_ERROR)
	{
	  printf("pack ip wsa address to string%d\n", WSAGetLastError());
	  throw;
	}
#endif
    }

    EndPoint	GetAnyIPEndPoint(short port)
    {
      return (EndPoint(net::ADDR_INET, NULL, port));
    }

    EndPoint	GetIPEndPoint(char const* ip, short port)
    {
      return (EndPoint(net::ADDR_INET, ip, port));
    }
  }

  namespace	ip6
  {
    void	packIP(char const* src, void* dst)
    {
      /* Non-implemented */
      (void) src;
      (void) dst;
    }

    void	unpackIP(void const* src, char* dst, size_t size)
    {
      /* Non-implemented */
      (void) src;
      (void) dst;
      (void) size;
    }

    EndPoint	GetAnyIPEndPoint(short port)
    {
      return (EndPoint(net::ADDR_INET6, NULL, port));
    }

    EndPoint	GetIPEndPoint(char const* ip, short port)
    {
      return (EndPoint(net::ADDR_INET6, ip, port));
    }
  }
}
