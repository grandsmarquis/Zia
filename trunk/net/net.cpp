#include	"net.hh"

namespace net
{
  short	hostToNetByteOrder(short s)
  {
    return (htons(s));
  }

  short	netToHostByteOrder(short s)
  {
    return (ntohs(s));
  }

  int	hostToNetByteOrder(int s)
  {
    return (htonl(s));
  }

  int	netToHostByteOrder(int s)
  {
    return (ntohl(s));
  }
}
