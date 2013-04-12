#include	<cstring>
#include	"ISocket.hh"

#ifndef	__AWINDOWS_SOCKET_HH__
#define	__AWINDOWS_SOCKET_HH__

#include <winsock2.h>
#include <ws2tcpip.h>

namespace      net
{
	class	AWindowsSocket : public ISocket
	{
	protected:
		SOCKET 	_sock;
		EndPoint	_remoteEndPoint;
	public:
		void	EndPointToWindowsAddr(EndPoint const& endPoint, struct sockaddr_in& addr);
		void	WindowsAddrToEndPoint(struct sockaddr_in const& addr, EndPoint& endPoint);
	public:
		virtual ~AWindowsSocket();
		AWindowsSocket();
		virtual ISocket*		Accept();
		virtual void		Bind(EndPoint& endPoint);
		virtual void		Close();
		virtual void		Connect(EndPoint& endPoint);
		//Connect();
		//Diconnect();
		//GetAvailableBytes();
		//GetOptions();
		virtual EndPoint const&   GetRemoteEndPoint() const;
		virtual void	SetRemoteEndPoint(EndPoint const& other);
		virtual void		Listen();
		virtual int		Recieve(char *buffer, size_t len);
		virtual int		RecieveFrom(char *buffer, size_t len, net::EndPoint& endPoint);
		virtual int		RecieveAll(char *buffer, size_t len);
		virtual int		Send(char *buffer, size_t len);
		virtual int		SendTo(char *buffer, size_t len, EndPoint const& endPoint);
		virtual int		SendAll(char *buffer, size_t len);
		SOCKET			GetSocketRepresentation();
		virtual bool			SetOptions(e_option opt);
		virtual int getFD() const
		{
			return (_sock);
		}
		/* ??? */
		virtual AWindowsSocket*	GetSocketForFd(int fd, struct sockaddr const& addr) = 0;
	};
}

#endif