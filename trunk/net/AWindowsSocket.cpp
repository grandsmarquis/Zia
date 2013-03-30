#include	"AWindowsSocket.hh"

/* printf -- DEBUG */
#include	<cstdio>
#include	<iostream>

namespace      net
{
	AWindowsSocket::AWindowsSocket()
	{
	  _sock = -1;
	}

	AWindowsSocket::~AWindowsSocket()
	{
	}

	ISocket*	AWindowsSocket::Accept()
	{
		struct sockaddr		addr;
		int			addr_len;
		int			client_sock;

		// TODO : crete ISocket and set sock remote endpoint
		addr_len = sizeof(SOCKADDR);
		if ((client_sock = WSAAccept(_sock, &addr, &addr_len, NULL, 0)) == -1) {
			//printf("%d\n", WSAGetLastError());
			return (NULL);
			//throw;
		}
		return (GetSocketForFd(client_sock, addr));
	}

	void	AWindowsSocket::EndPointToWindowsAddr(EndPoint const& endPoint, struct sockaddr_in& addr)
	{
		int			addrLen;

		addr.sin_family = AF_INET;
		addr.sin_port = endPoint.GetAddrPort();
		endPoint.GetAddrData(&addr.sin_addr, &addrLen);
	}

	void	AWindowsSocket::WindowsAddrToEndPoint(struct sockaddr_in const& addr, EndPoint& endPoint)
	{
		int			addrLen;

		endPoint.SetAddrFamily(net::ADDR_INET);
		endPoint.SetAddrPort(addr.sin_port);
		endPoint.SetAddrData(reinterpret_cast<void const*>(&addr.sin_addr), sizeof(addr.sin_addr));
	}

	void	AWindowsSocket::Bind(EndPoint& endPoint)
	{
		struct ::sockaddr_in	addr;

		EndPointToWindowsAddr(endPoint, addr);
		if (bind(_sock, (SOCKADDR*)&addr, sizeof(SOCKADDR)) == -1) {
			printf("Bind: %d\n", WSAGetLastError());
			throw std::exception();
		}
		_remoteEndPoint = endPoint;
	}

	void	AWindowsSocket::Connect(EndPoint& endPoint)
	{
		struct sockaddr_in	addr;

		EndPointToWindowsAddr(endPoint, addr);
		if (WSAConnect(_sock, (SOCKADDR*)&addr, sizeof(SOCKADDR), NULL, NULL, NULL, NULL) == SOCKET_ERROR)
		{		
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				std::cout << "connect -> getLastError()" << WSAGetLastError() << std::endl;
				throw std::exception();
			}
		}
		_remoteEndPoint = endPoint;
	}

	int	AWindowsSocket::Recieve(char *buffer, size_t len)
	{
		DWORD 		recvBytes;
		WSABUF		WSAbuffer;
		DWORD 		flags = 0;
		//WSAOVERLAPPED	whatIsThis; // TODO

		WSAbuffer.buf = buffer;
		WSAbuffer.len = len;
		if (WSARecv(_sock, &WSAbuffer, 1, &recvBytes, &flags, NULL, NULL) != 0)
		{
			return (-1);
		}
		return (recvBytes);
	}

	int	AWindowsSocket::RecieveFrom(char *buffer, size_t len, net::EndPoint& endPoint)
	{
		DWORD 		recvBytes;
		WSABUF		WSAbuffer;
		DWORD 		flags = 0;
		SOCKADDR_IN	addr;
		INT	addrLen = sizeof(struct sockaddr);
		//WSAOVERLAPPED	whatIsThis; // TODO

		WSAbuffer.buf = buffer;
		WSAbuffer.len = len;
		if (WSARecvFrom(_sock, &WSAbuffer, 1, &recvBytes, &flags, (SOCKADDR*)&addr, &addrLen, NULL, NULL) != 0)
		{
			return (-1);
		}
		WindowsAddrToEndPoint(addr, endPoint);
		return (recvBytes);
	}

	int	AWindowsSocket::RecieveAll(char *buffer, size_t len)
	{
		return (-1);
	}

	int	AWindowsSocket::Send(char *buffer, size_t len)
	{
		DWORD 		sendBytes;
		WSABUF		WSAbuffer;
		DWORD 		flags = 0;
		//WSAOVERLAPPED	whatIsThis; // TODO

		WSAbuffer.buf = buffer;
		WSAbuffer.len = len;
		if (WSASend(_sock, &WSAbuffer, 1, &sendBytes, 0, NULL, NULL) != 0)
		{
			return (-1);
		}
		return (sendBytes);
	}

	int	AWindowsSocket::SendTo(char *buffer, size_t len, EndPoint const& endPoint)
	{
		DWORD 		sendBytes;
		WSABUF		WSAbuffer;
		DWORD 		flags = 0;
		SOCKADDR_IN	addr;
		INT	addrLen = sizeof(struct sockaddr);
		//WSAOVERLAPPED	whatIsThis; // TODO

		WSAbuffer.buf = buffer;
		WSAbuffer.len = len;
		EndPointToWindowsAddr(endPoint, addr);
		if (WSASendTo(_sock, &WSAbuffer, 1, &sendBytes, 0, (SOCKADDR*)&addr, addrLen, NULL, NULL) != 0)
		{
			return (-1);
		}
		return (sendBytes);
	}

	int	AWindowsSocket::SendAll(char *buffer, size_t len)
	{
		 int		sentBytes = 0;
		int		    ret;
		DWORD 		sendBytes;
		WSABUF		WSAbuffer;

    while (static_cast<size_t>(sentBytes) < len)
      {
		WSAbuffer.buf = buffer + sentBytes;
		WSAbuffer.len = len - sentBytes;
		if (WSASend(_sock, &WSAbuffer, 1, &sendBytes, 0, NULL, NULL) != 0)
			{
				std::cout << "Error Send All error_id == " << WSAGetLastError() << std::endl;
				return (-1);
			}
		else if (sendBytes > 0)
			sentBytes += sendBytes;
      }
    return (sentBytes);
	}

	bool	AWindowsSocket::SetOptions(e_option opt)
	{
		int ret;
		if (opt == net::ISocket::O_NONBLOCKING)
		{
			u_long mode = 1;
			ret = ioctlsocket(_sock, FIONBIO, &mode);
			return (ret != NO_ERROR);
		}
		else if (opt == net::ISocket::O_REUSEADDR)
		{
			int reuse = 1;
			ret = setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse, sizeof (reuse));
			return (ret != SOCKET_ERROR);
		}
		return (true);
	}

	void	AWindowsSocket::Listen()
	{
		if (listen(_sock, 0))
			throw std::exception();
	}

	EndPoint const&	AWindowsSocket::GetRemoteEndPoint() const
	{
		return (_remoteEndPoint);
	}
	
	SOCKET	AWindowsSocket::GetSocketRepresentation()
	{
		return (_sock);
	}

	void		AWindowsSocket::Close()
	{
		closesocket(_sock);
		_sock = -1;
	}

	void	AWindowsSocket::SetRemoteEndPoint(EndPoint const& other)
	{
		_remoteEndPoint = other;
	}
}
