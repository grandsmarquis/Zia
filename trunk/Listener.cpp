#include "Listener.hpp"

Listener::Listener(int port)
  :_port(port)
{
  this->initTCP(port);
}

bool Listener::initTCP(int port)
{
  this->_endPoint = net::ip::GetAnyIPEndPoint(port);
#ifdef __unix__
  this->_socket = new net::UnixThreadSafeSocket(new net::ip::tcp::LinuxSocket());
#elif defined _WIN32
  this->_socket = new net::ip::tcp::WindowsSocket();
#endif
  this->_socket->SetOptions(net::ISocket::O_NONBLOCKING);
  _good = true;
  try
    {
      this->_socket->Bind(this->_endPoint);
      this->_socket->Listen();
    }
  catch (std::exception const& e)
    {
      _good = false;
    }
  return (true);
}

int Listener::getPort(void) const
{
  return (this->_port);
}

net::ISocket *Listener::getNewClient(void)
{
  return (this->_socket->Accept());
}

bool Listener::succeedBind() const
{
  return (_good);
}
