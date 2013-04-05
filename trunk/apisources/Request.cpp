
#include "Request.h"
#include "../HTTPParser.hpp"

Request::Request(char *buffer, int bufferLength)
  : _body(buffer, bufferLength)
{
  HTTPParser parser(buffer, bufferLength);
  _header.setCommand(parser.getCmd());
  _header.setArg(parser.getArg());
  _header.setVersion(parser.getVersion());
  std::cout << parser.getCmd() << " }} " << parser.getArg() << " }} " << parser.getVersion() << std::endl;
  for (std::map<std::string, std::string>::const_iterator it = parser.getMap().begin(); it != parser.getMap().end(); ++it)
    {
      std::cout << it->first << " }}{{ " << it->second << std::endl;
      _header.setValue(it->first, it->second);
    }
}

Request::~Request()
{

}

Body	&Request::getBody()
{
  return (_body);
}

char	*Request::getBuffer()
{
  return (_buffer);
}

RequestHeader &Request::getHeader()
{
  return (_header);
}

int Request::getLength() const
{
  return (_bufferLength);
}

void Request::separate()
{

}
