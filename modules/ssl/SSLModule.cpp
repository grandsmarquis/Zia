
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>

#include "../../trunk/apiheaders/ModuleInfos.h"
#include "../../trunk/apiheaders/Directives.h"
#include "../../trunk/apiheaders/DirectivesOrder.h"

#include "SSLModule.hpp"

extern "C"
{
  ModuleInfos * get_module_infos()
  {
    ModuleInfos *m = new ModuleInfos;

    m->associatedDLL = "SSL";
    m->managedDirectives = CREATE_RESPONSE; // CONNECTION_INIT | PREPROCESS_REQUEST | PROCESS_FINISHED_RESPONSE;
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
  boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);

  context.set_options(
      boost::asio::ssl::context::default_workarounds
      | boost::asio::ssl::context::no_sslv2
      | boost::asio::ssl::context::single_dh_use);
  context.set_password_callback(boost::bind(&SSLModule::get_password, this));
  context.use_certificate_chain_file("server.crt");
  context.use_private_key_file("server.key", boost::asio::ssl::context::pem);

}

void SSLModule::callDirective(DirectivesOrder directiveorder, Request & request, Response & response, t_socket socket, sockaddr_in connexionInfos)
{

}
