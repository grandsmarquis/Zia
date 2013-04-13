
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "../../trunk/apiheaders/ModuleInfos.h"
#include "../../trunk/apiheaders/Directives.h"
#include "../../trunk/apiheaders/DirectivesOrder.h"

#include "SSLModule.hpp"

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket &> ssl_socket;

class session
{
public:
  session(ssl_socket & sock,
      boost::asio::ssl::context& context)
    : socket_(sock)
  {
  }

  ssl_socket::lowest_layer_type& socket()
  {
    return socket_.lowest_layer();
  }

  void start()
  {
    socket_.async_handshake(boost::asio::ssl::stream_base::server,
        boost::bind(&session::handle_handshake, this,
          boost::asio::placeholders::error));
  }

  void handle_handshake(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }

  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
      boost::asio::async_write(socket_,
          boost::asio::buffer(data_, bytes_transferred),
          boost::bind(&session::handle_write, this,
            boost::asio::placeholders::error));
    }
    else
    {
      delete this;
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }

private:
  ssl_socket & socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};



extern "C"
{
  ModuleInfos * get_module_infos()
  {
    ModuleInfos *m = new ModuleInfos;

    m->associatedDLL = "SSL";
    m->managedDirectives = PREPROCESS_REQUEST; // CREATE_RESPONSE; // CONNECTION_INIT | PREPROCESS_REQUEST | PROCESS_FINISHED_RESPONSE;
    m->managesHeaderOnly = true;
    m->name = "ssl";
    m->nbDirectives = 1;
    return (m);
  }

  Directives * get_directives()
  {
    return (new SSLModule());
  }
}

SSLModule::SSLModule()
{
  std::cout << "NEW SSL"<<std::endl;
}

SSLModule::~SSLModule()
{
}

std::string SSLModule::get_password() const
{
  return "test";
}

void SSLModule::init()
{
}

void SSLModule::callDirective(DirectivesOrder directiveorder, Request & request, Response & response, t_socket sock, struct sockaddr_in & connexionInfos)
{
  /*
  boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);

  context.set_options(
      boost::asio::ssl::context::default_workarounds
      | boost::asio::ssl::context::no_sslv2
      | boost::asio::ssl::context::single_dh_use);
  context.set_password_callback(boost::bind(&SSLModule::get_password, this));
  context.use_certificate_chain_file("server.crt");
  context.use_private_key_file("server.key", boost::asio::ssl::context::pem);
  */

  std::cout << "lol"<<std::endl;
  /*
  size_t length = 128;
  char *buff = new char[128];
  boost::system::error_code error;

  boost::asio::io_service io_service;
  boost::asio::ip::tcp::socket t(io_service);
  t.assign(boost::asio::ip::tcp::v4(), sock);

  boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket &> ssl_sock(t, context);

  context.set_options(
      boost::asio::ssl::context::default_workarounds
      | boost::asio::ssl::context::no_sslv2
      | boost::asio::ssl::context::single_dh_use);
  context.set_password_callback(boost::bind(&SSLModule::get_password, this));
  context.use_certificate_chain_file("server.crt");
  context.use_private_key_file("server.key", boost::asio::ssl::context::pem);

  session* new_session = new session(ssl_sock, context);
  new_session->start();
*/

  /*
  context.set_options(
      boost::asio::ssl::context::default_workarounds
      | boost::asio::ssl::context::no_sslv2
      | boost::asio::ssl::context::single_dh_use);
  context.set_password_callback(boost::bind(&SSLModule::get_password, this));
  context.use_certificate_chain_file("server.crt");
  context.use_private_key_file("server.key", boost::asio::ssl::context::pem);


  boost::asio::ssl::stream<boost::asio::ip::tcp::socket &> ssl_socket(t, context);

  ssl_socket.handshake(boost::asio::ssl::stream_base::server, error);
  if (error) {
    std::cout << "error " << error << std::endl;
  } else {
    std::cout << "ok" << std::endl;
  }
  ssl_socket.read_some(boost::asio::buffer(buff, length));
  std::cout.write(buff, length);
  // ssl_socket
  */

}
